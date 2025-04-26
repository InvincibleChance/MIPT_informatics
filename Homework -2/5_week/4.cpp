#include <random>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "button.hpp"

float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
}

int getRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d(min, max);
    return d(gen);
}

sf::Color getRandomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
}

class ShapePool
{
protected:
    sf::RectangleShape mField;
    std::vector<sf::Shape*> mShapes;
    sf::RenderWindow& mRenderWindow;

public:
    ShapePool(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size)
    : mRenderWindow(window)
    {
        mField.setPosition(position);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0, 100, 200, 40));
    }

    void addShape(sf::Shape* p)
    {
        p->setOrigin(p->getGlobalBounds().getSize() / 2.f);
        sf::Vector2f min = p->getGlobalBounds().getSize() / 2.f;
        sf::Vector2f max = mField.getSize() - p->getGlobalBounds().getSize() / 2.f;
        p->setPosition(mField.getPosition() + sf::Vector2f(
            getRandomFloat(min.x, max.x),
            getRandomFloat(min.y, max.y)
        ));
        p->setFillColor(getRandomColor());
        mShapes.push_back(p);
    }

    size_t getNumOfShapes() const { return mShapes.size(); }
    sf::Vector2f getPosition() const { return mField.getPosition(); }
    sf::Vector2f getSize() const { return mField.getSize(); }

    sf::Shape& getShape(int index)
    {
        return *mShapes.at(index);
    }

    void clearShapes()
    {
        for (auto* p : mShapes)
            delete p;
        mShapes.clear();
    }

    void draw() const
    {
        for (auto p : mShapes)
            mRenderWindow.draw(*p);
        mRenderWindow.draw(mField);
    }

    ~ShapePool()
    {
        clearShapes();
    }
};


class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class NoCommand : public Command
{
public:
    void execute() override {}
};

class RotateCommand : public Command
{
protected:
    ShapePool& mPool;
    size_t mIndex;
    float mAngle;
public:
    RotateCommand(ShapePool& pool, size_t index, float angle)
    : mPool(pool), mIndex(index), mAngle(angle) {}
    void execute() override
    {
        mPool.getShape(mIndex).rotate(mAngle);
    }
};

class RandomColorCommand : public Command
{
protected:
    ShapePool& mPool;
    size_t mIndex;
public:
    RandomColorCommand(ShapePool& pool, size_t index)
    : mPool(pool), mIndex(index) {}
    void execute() override
    {
        mPool.getShape(mIndex).setFillColor(getRandomColor());
    }
};

class RandomAllColorsCommand : public Command
{
protected:
    ShapePool& mPool;
public:
    RandomAllColorsCommand(ShapePool& pool)
    : mPool(pool) {}
    void execute() override
    {
        for (size_t i = 0; i < mPool.getNumOfShapes(); ++i)
            mPool.getShape(i).setFillColor(getRandomColor());
    }
};

class RandomAllPositionsCommand : public Command
{
protected:
    ShapePool& mPool;
public:
    RandomAllPositionsCommand(ShapePool& pool)
    : mPool(pool) {}
    void execute() override
    {
        for (size_t i = 0; i < mPool.getNumOfShapes(); ++i)
        {
            sf::Shape& shape = mPool.getShape(i);
            sf::Vector2f min = shape.getGlobalBounds().getSize() / 2.f;
            sf::Vector2f max = mPool.getSize() - shape.getGlobalBounds().getSize() / 2.f;
            shape.setPosition(
                mPool.getPosition() + sf::Vector2f(
                    getRandomFloat(min.x, max.x),
                    getRandomFloat(min.y, max.y)
                )
            );
        }
    }
};

class AddNewRandomShape : public Command
{
protected:
    ShapePool& mPool;
    float mMinSize;
    float mMaxSize;
public:
    AddNewRandomShape(ShapePool& pool, float minSize, float maxSize)
    : mPool(pool), mMinSize(minSize), mMaxSize(maxSize) {}
    void execute() override
    {
        int r = getRandomInt(0, 2);
        sf::Shape* ps;
        if (r == 0)
            ps = new sf::RectangleShape({getRandomFloat(mMinSize, mMaxSize), getRandomFloat(mMinSize, mMaxSize)});
        else if (r == 1)
            ps = new sf::CircleShape(getRandomFloat(mMinSize/2.f, mMaxSize/2.f));
        else
            ps = new sf::CircleShape(getRandomFloat(mMinSize/2.f, mMaxSize/2.f), 3);
        ps->setFillColor(getRandomColor());
        ps->rotate(getRandomFloat(0.f, 360.f));
        sf::FloatRect bounds = ps->getGlobalBounds();
        ps->setPosition(
            mPool.getPosition().x + getRandomFloat(0.f, mPool.getSize().x - bounds.width),
            mPool.getPosition().y + getRandomFloat(0.f, mPool.getSize().y - bounds.height)
        );
        mPool.addShape(ps);
    }
};


class DeleteAllShapesCommand : public Command
{
protected:
    ShapePool& mPool;
public:
    DeleteAllShapesCommand(ShapePool& pool)
    : mPool(pool) {}
    void execute() override
    {
        mPool.clearShapes();
    }
};

class ControlPanel
{
protected:
    std::vector<Button*> mButtons;
    std::vector<Command*> mCommands;
    sf::RenderWindow& mRenderWindow;
public:
    ControlPanel(sf::RenderWindow& window)
    : mRenderWindow(window) {}
    void addButton(Button* b)
    {
        mButtons.push_back(b);
        mCommands.push_back(new NoCommand);
    }
    void addButton(Button* b, Command* c)
    {
        mButtons.push_back(b);
        mCommands.push_back(c);
    }
    void draw() const
    {
        for (auto b : mButtons)
            b->draw();
    }
    void handleEvent(const sf::Event& ev)
    {
        for (size_t i = 0; i < mButtons.size(); ++i)
            if (mButtons[i]->handleEvent(ev))
                mCommands[i]->execute();
    }
    ~ControlPanel()
    {
        for (auto* b : mButtons) delete b;
        for (auto* c : mCommands) delete c;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Shapes and Command");
    sf::Font font; 

    ShapePool pool(window, {300,50}, {450,700});
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150), getRandomFloat(50,150)}));
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150), getRandomFloat(50,150)}));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100), 3));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));

    ControlPanel control(window);
    control.addButton(new Button(window, {40, 80, 240, 40}, font, 20, sf::String("Rotate First")),
                      new RotateCommand(pool, 0, 30));
    control.addButton(new Button(window, {40,140,240,40}, font, 20, sf::String("Rotate Second")),
                      new RotateCommand(pool, 1, 45));
    control.addButton(new Button(window, {40,200,240,40}, font, 20, sf::String("One Color")),
                      new RandomColorCommand(pool, 3));
    control.addButton(new Button(window, {40,260,240,40}, font, 20, sf::String("Rand Positions")),
                      new RandomAllPositionsCommand(pool));
    control.addButton(new Button(window, {40,320,240,40}, font, 20, sf::String("New Shape")),
                      new AddNewRandomShape(pool, 10, 150));
    control.addButton(new Button(window, {40,380,240,40}, font, 20, sf::String("Rand Colors")),
                      new RandomAllColorsCommand(pool));
    control.addButton(new Button(window, {40,440,240,40}, font, 20, sf::String("Clear All")),
                      new DeleteAllShapesCommand(pool));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            control.handleEvent(event);
        }
        window.clear(sf::Color::Black);
        pool.draw();
        control.draw();
        window.display();
    }
}
