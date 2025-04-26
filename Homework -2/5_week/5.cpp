#include <random>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "button.hpp"

auto getRandomFloat = [](float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
};

auto getRandomInt = [](int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d(min, max);
    return d(gen);
};

auto getRandomColor = []() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
};

class ShapePool {
protected:
    sf::RectangleShape mField;
    std::vector<sf::Shape*> mShapes;
    sf::RenderWindow& mWindow;

public:
    ShapePool(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size)
        : mWindow(window) {
        mField.setPosition(pos);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0, 100, 200, 40));
    }

    void addShape(sf::Shape* shape) {
        shape->setOrigin(shape->getGlobalBounds().getSize() / 2.f);
        sf::Vector2f min = shape->getGlobalBounds().getSize() / 2.f;
        sf::Vector2f max = mField.getSize() - shape->getGlobalBounds().getSize() / 2.f;
        shape->setPosition(mField.getPosition() + sf::Vector2f(
            getRandomFloat(min.x, max.x),
            getRandomFloat(min.y, max.y)
        ));
        shape->setFillColor(getRandomColor());
        mShapes.push_back(shape);
    }

    size_t getNumOfShapes() const { return mShapes.size(); }
    sf::Vector2f getPosition() const { return mField.getPosition(); }
    sf::Vector2f getSize() const { return mField.getSize(); }

    sf::Shape& getShape(size_t idx) { return *mShapes.at(idx); }

    void clearShapes() {
        for (auto* s : mShapes) delete s;
        mShapes.clear();
    }

    void draw() const {
        for (auto* s : mShapes) mWindow.draw(*s);
        mWindow.draw(mField);
    }

    ~ShapePool() { clearShapes(); }
};

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class NoCommand : public Command {
public:
    void execute() override {}
};

class RotateCommand : public Command {
    ShapePool& mPool;
    size_t mIdx;
    float mAngle;
public:
    RotateCommand(ShapePool& pool, size_t idx, float angle)
        : mPool(pool), mIdx(idx), mAngle(angle) {}
    void execute() override { mPool.getShape(mIdx).rotate(mAngle); }
};

class RandomColorCommand : public Command {
    ShapePool& mPool;
    size_t mIdx;
public:
    RandomColorCommand(ShapePool& pool, size_t idx)
        : mPool(pool), mIdx(idx) {}
    void execute() override { mPool.getShape(mIdx).setFillColor(getRandomColor()); }
};

class RandomAllColorsCommand : public Command {
    ShapePool& mPool;
public:
    RandomAllColorsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        for (size_t i = 0; i < mPool.getNumOfShapes(); ++i)
            mPool.getShape(i).setFillColor(getRandomColor());
    }
};

class RandomAllPositionsCommand : public Command {
    ShapePool& mPool;
public:
    RandomAllPositionsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        for (size_t i = 0; i < mPool.getNumOfShapes(); ++i) {
            auto& shape = mPool.getShape(i);
            sf::Vector2f min = shape.getGlobalBounds().getSize() / 2.f;
            sf::Vector2f max = mPool.getSize() - shape.getGlobalBounds().getSize() / 2.f;
            shape.setPosition(mPool.getPosition() + sf::Vector2f(
                getRandomFloat(min.x, max.x),
                getRandomFloat(min.y, max.y)
            ));
        }
    }
};

class AddNewRandomShape : public Command {
    ShapePool& mPool;
    float mMin, mMax;
public:
    AddNewRandomShape(ShapePool& pool, float minSize, float maxSize)
        : mPool(pool), mMin(minSize), mMax(maxSize) {}
    void execute() override {
        int r = getRandomInt(0, 2);
        sf::Shape* shape = nullptr;
        if (r == 0)
            shape = new sf::RectangleShape({ getRandomFloat(mMin, mMax), getRandomFloat(mMin, mMax) });
        else if (r == 1)
            shape = new sf::CircleShape(getRandomFloat(mMin/2, mMax/2));
        else
            shape = new sf::CircleShape(getRandomFloat(mMin/2, mMax/2), 3);
        shape->setFillColor(getRandomColor());
        shape->rotate(getRandomFloat(0,360));
        sf::FloatRect b = shape->getGlobalBounds();
        shape->setPosition(
            mPool.getPosition().x + getRandomFloat(0,mPool.getSize().x - b.width),
            mPool.getPosition().y + getRandomFloat(0,mPool.getSize().y - b.height)
        );
        mPool.addShape(shape);
    }
};

class DeleteAllShapesCommand : public Command {
    ShapePool& mPool;
public:
    DeleteAllShapesCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override { mPool.clearShapes(); }
};

class MultiCommand : public Command {
    std::vector<Command*> mCommands;
public:
    MultiCommand(std::vector<Command*> cmds) : mCommands(std::move(cmds)) {}
    void execute() override {
        for (auto* cmd : mCommands) cmd->execute();
    }
    ~MultiCommand() {
        for (auto* cmd : mCommands) delete cmd;
    }
};

class ControlPanel {
    std::vector<Button*> mButtons;
    std::vector<Command*> mCmds;
    sf::RenderWindow& mWindow;
public:
    ControlPanel(sf::RenderWindow& win) : mWindow(win) {}
    void addButton(Button* b, Command* c = new NoCommand) {
        mButtons.push_back(b);
        mCmds.push_back(c);
    }
    void draw() const { for (auto* b : mButtons) b->draw(); }
    void handleEvent(const sf::Event& ev) {
        for (size_t i = 0; i < mButtons.size(); ++i)
            if (mButtons[i]->handleEvent(ev))
                mCmds[i]->execute();
    }
    ~ControlPanel() {
        for (auto* b : mButtons) delete b;
        for (auto* c : mCmds) delete c;
    }
};

int main(){
    sf::RenderWindow window({800,800}, "Shapes and Command");
    sf::Font font; 

    ShapePool pool(window, {300,50}, {450,700});
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150), getRandomFloat(50,150)}));
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150), getRandomFloat(50,150)}));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100),3));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));

    ControlPanel control(window);
    control.addButton(new Button(window,{40,80,240,40}, font, 20, sf::String("Rotate1")),
                      new RotateCommand(pool,0,30));
    control.addButton(new Button(window,{40,140,240,40},font,20, sf::String("Rotate2")),
                      new RotateCommand(pool,1,45));
    control.addButton(new Button(window,{40,200,240,40},font,20, sf::String("Color1")),
                      new RandomColorCommand(pool,3));
    control.addButton(new Button(window,{40,260,240,40},font,20, sf::String("PosAll")),
                      new RandomAllPositionsCommand(pool));
    control.addButton(new Button(window,{40,320,240,40},font,20, sf::String("New")),
                      new AddNewRandomShape(pool,10,150));
    control.addButton(new Button(window,{40,380,240,40},font,20, sf::String("ColorAll")),
                      new RandomAllColorsCommand(pool));
    control.addButton(new Button(window,{40,440,240,40},font,20, sf::String("ClearAll")),
                      new DeleteAllShapesCommand(pool));
    std::vector<Command*> multiCmds = {
        new RandomAllColorsCommand(pool),
        new RandomAllPositionsCommand(pool)
    };
    control.addButton(new Button(window,{40,500,240,40},font,20, sf::String("RandAll")),
                      new MultiCommand(multiCmds));

    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if(ev.type==sf::Event::Closed) window.close();
            control.handleEvent(ev);
        }
        window.clear(sf::Color::Black);
        pool.draw();
        control.draw();
        window.display();
    }
}
