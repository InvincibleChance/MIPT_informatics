#include <random>
#include <cstdlib>
#include <memory>
#include "SFML/Graphics.hpp"
#include "button.hpp"

static auto getRandomFloat = [](float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
};

static auto getRandomInt = [](int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d(min, max);
    return d(gen);
};

static auto getRandomColor = []() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
};

class ShapePool {
    sf::RectangleShape mField;
    std::vector<std::unique_ptr<sf::Shape>> mShapes;
    sf::RenderWindow& mWindow;
public:
    ShapePool(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size)
        : mWindow(window) {
        mField.setPosition(pos);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0,100,200,40));
    }
    void addShape(std::unique_ptr<sf::Shape> s) {
        s->setOrigin(s->getGlobalBounds().getSize()/2.f);
        auto min = s->getGlobalBounds().getSize()/2.f;
        auto max = mField.getSize() - s->getGlobalBounds().getSize()/2.f;
        s->setPosition(mField.getPosition() + sf::Vector2f(
            getRandomFloat(min.x,max.x), getRandomFloat(min.y,max.y)
        ));
        s->setFillColor(getRandomColor());
        mShapes.push_back(std::move(s));
    }
    size_t getNum() const { return mShapes.size(); }
    sf::Shape& get(size_t i) { return *mShapes.at(i); }
    sf::Vector2f getPos() const { return mField.getPosition(); }
    sf::Vector2f getSize() const { return mField.getSize(); }
    std::vector<sf::Vector2f> getPositions() const {
        std::vector<sf::Vector2f> v;
        for (auto& up: mShapes) v.push_back(up->getPosition());
        return v;
    }
    std::vector<sf::Color> getColors() const {
        std::vector<sf::Color> v;
        for (auto& up: mShapes) v.push_back(up->getFillColor());
        return v;
    }
    void removeLast() {
        if (!mShapes.empty()) mShapes.pop_back();
    }
    void clearAll() {
        mShapes.clear();
    }
    void draw() const {
        for (auto& up: mShapes) mWindow.draw(*up);
        mWindow.draw(mField);
    }
};

class Command {
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual ~Command() = default;
};

class NoCommand : public Command {
public:
    void execute() override {}
    void unexecute() override {}
};

class RotateCommand : public Command {
    ShapePool& pool;
    size_t idx;
    float angle;
public:
    RotateCommand(ShapePool& p, size_t i, float a)
        : pool(p), idx(i), angle(a) {}
    void execute() override { pool.get(idx).rotate(angle); }
    void unexecute() override { pool.get(idx).rotate(-angle); }
};

class RandomColorCommand : public Command {
    ShapePool& pool;
    size_t idx;
    sf::Color old;
public:
    RandomColorCommand(ShapePool& p, size_t i)
        : pool(p), idx(i) {}
    void execute() override {
        old = pool.get(idx).getFillColor();
        pool.get(idx).setFillColor(getRandomColor());
    }
    void unexecute() override { pool.get(idx).setFillColor(old); }
};

class RandomAllColorsCommand : public Command {
    ShapePool& pool;
    std::vector<sf::Color> old;
public:
    RandomAllColorsCommand(ShapePool& p) : pool(p) {}
    void execute() override {
        old = pool.getColors();
        for (size_t i=0; i<pool.getNum(); ++i)
            pool.get(i).setFillColor(getRandomColor());
    }
    void unexecute() override {
        for (size_t i=0; i<pool.getNum() && i<old.size(); ++i)
            pool.get(i).setFillColor(old[i]);
    }
};

class RandomAllPositionsCommand : public Command {
    ShapePool& pool;
    std::vector<sf::Vector2f> old;
public:
    RandomAllPositionsCommand(ShapePool& p) : pool(p) {}
    void execute() override {
        old = pool.getPositions();
        for (size_t i=0; i<pool.getNum(); ++i) {
            auto& s = pool.get(i);
            auto min = s.getGlobalBounds().getSize()/2.f;
            auto max = pool.getSize() - s.getGlobalBounds().getSize()/2.f;
            s.setPosition(pool.getPos()+ sf::Vector2f(getRandomFloat(min.x,max.x),getRandomFloat(min.y,max.y)));
        }
    }
    void unexecute() override {
        for (size_t i=0; i<pool.getNum() && i<old.size(); ++i)
            pool.get(i).setPosition(old[i]);
    }
};

class AddNewRandomShape : public Command {
    ShapePool& pool;
    float minS, maxS;
    bool addedFlag{false};
public:
    AddNewRandomShape(ShapePool& p, float mi, float ma)
        : pool(p), minS(mi), maxS(ma) {}
    void execute() override {
        std::unique_ptr<sf::Shape> shape;
        int r = getRandomInt(0,2);
        if (r==0)
            shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(getRandomFloat(minS,maxS),getRandomFloat(minS,maxS)));
        else if(r==1)
            shape = std::make_unique<sf::CircleShape>(getRandomFloat(minS/2, maxS/2));
        else
            shape = std::make_unique<sf::CircleShape>(getRandomFloat(minS/2,maxS/2),3);
        shape->setFillColor(getRandomColor());
        shape->rotate(getRandomFloat(0,360));
        auto b = shape->getGlobalBounds();
        shape->setPosition(pool.getPos()+ sf::Vector2f(getRandomFloat(0,pool.getSize().x-b.width), getRandomFloat(0,pool.getSize().y-b.height)));
        pool.addShape(std::move(shape));
        addedFlag = true;
    }
    void unexecute() override {
        if (addedFlag) { pool.removeLast(); addedFlag=false; }
    }
};

class DeleteAllShapesCommand : public Command {
    ShapePool& pool;
    std::vector<std::unique_ptr<sf::Shape>> backup;
public:
    DeleteAllShapesCommand(ShapePool& p) : pool(p) {}
    void execute() override {
        backup.clear();
        for (size_t i=0; i<pool.getNum(); ++i) {
            auto& up = pool.get(i);
        }
        pool.clearAll();
    }
    void unexecute() override {
    }
};

class MultiCommand : public Command {
    std::vector<std::unique_ptr<Command>> cmds;
public:
    MultiCommand(std::vector<std::unique_ptr<Command>> v) : cmds(std::move(v)) {}
    void execute() override { for (auto& c: cmds) c->execute(); }
    void unexecute() override { for (auto it=cmds.rbegin(); it!=cmds.rend(); ++it) (*it)->unexecute(); }
};

class ControlPanel {
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::unique_ptr<Command>> cmds;
    std::vector<Command*> history;
    sf::RenderWindow& window;
public:
    ControlPanel(sf::RenderWindow& w) : window(w) {}
    void add(std::unique_ptr<Button> b, std::unique_ptr<Command> c) {
        cmds.push_back(std::move(c));
        history.emplace_back();
        buttons.push_back(std::move(b));
    }
    void draw() const { for (auto& b: buttons) b->draw(); }
    void handle(const sf::Event& ev) {
        for (size_t i=0; i<buttons.size(); ++i) {
            if (buttons[i]->handleEvent(ev)) {
                cmds[i]->execute();
                history.push_back(cmds[i].get());
            }
        }
    }
    void undo() {
        if (!history.empty()) {
            history.back()->unexecute();
            history.pop_back();
        }
    }
};

int main() {
    sf::RenderWindow window({800,800},"Shapes and Command");
    sf::Font font;
    ShapePool pool(window,{300,50},{450,700});
    pool.addShape(std::make_unique<sf::RectangleShape>(sf::Vector2f(getRandomFloat(50,150),getRandomFloat(50,150))));
    pool.addShape(std::make_unique<sf::RectangleShape>(sf::Vector2f(getRandomFloat(50,150),getRandomFloat(50,150))));
    pool.addShape(std::make_unique<sf::CircleShape>(getRandomFloat(30,100),3));
    pool.addShape(std::make_unique<sf::CircleShape>(getRandomFloat(30,100)));
    pool.addShape(std::make_unique<sf::CircleShape>(getRandomFloat(30,100)));

    ControlPanel control(window);
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,80,240,40},font,20,"Rotate1"),
                std::make_unique<RotateCommand>(pool,0,30));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,140,240,40},font,20,"Rotate2"),
                std::make_unique<RotateCommand>(pool,1,45));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,200,240,40},font,20,"Color1"),
                std::make_unique<RandomColorCommand>(pool,2));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,260,240,40},font,20,"PosAll"),
                std::make_unique<RandomAllPositionsCommand>(pool));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,320,240,40},font,20,"New"),
                std::make_unique<AddNewRandomShape>(pool,10,150));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,380,240,40},font,20,"ColorAll"),
                std::make_unique<RandomAllColorsCommand>(pool));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,440,240,40},font,20,"ClearAll"),
                std::make_unique<DeleteAllShapesCommand>(pool));
    std::vector<std::unique_ptr<Command>> m;
    m.push_back(std::make_unique<RandomAllColorsCommand>(pool));
    m.push_back(std::make_unique<RandomAllPositionsCommand>(pool));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,500,240,40},font,20,"RandAll"),
                std::make_unique<MultiCommand>(std::move(m)));
    control.add(std::make_unique<Button>(window, sf::FloatRect{40,560,240,40},font,20,"Undo"),
                std::make_unique<NoCommand>());

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            control.handle(ev);
            if (ev.type==sf::Event::MouseButtonPressed && ev.mouseButton.button==sf::Mouse::Left
                && ev.mouseButton.x>=40&&ev.mouseButton.x<=280&&ev.mouseButton.y>=560&&ev.mouseButton.y<=600) {
                control.undo();
            }
        }
        window.clear();
        pool.draw();
        control.draw();
        window.display();
    }
}
