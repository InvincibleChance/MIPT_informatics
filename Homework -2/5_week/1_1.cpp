#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <set>

class Observer
{
public:
    virtual void update(float value) = 0;
    virtual ~Observer() = default;
};

class Subject
{
public:
    virtual void addObserver(Observer* p) = 0;
    virtual void removeObserver(Observer* p) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable, public Subject
{
protected:
    sf::RectangleShape mTrackShape;
    sf::RectangleShape mThumbShape;
    sf::Color mTrackColor {200, 200, 220};
    sf::Color mThumbColor {150, 150, 240};
    sf::RenderWindow& mRenderWindow;
    bool mIsPressed {false};
    std::set<Observer*> mObservers;

public:
    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize)
        : mRenderWindow(window)
    {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.f);
        mTrackShape.setPosition(centerPosition);
        mTrackShape.setFillColor(mTrackColor);

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.f);
        mThumbShape.setPosition(centerPosition);
        mThumbShape.setFillColor(mThumbColor);
    }

    void draw() const override
    {
        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }

    void handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseMoved && mIsPressed)
        {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            float minX = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.f;
            float maxX = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.f;
            float clampedX = std::clamp(mousePos.x, minX, maxX);
            mThumbShape.setPosition(clampedX, mThumbShape.getPosition().y);
            notifyObservers();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mTrackShape.getGlobalBounds().contains(mousePos) || mThumbShape.getGlobalBounds().contains(mousePos))
            {
                mIsPressed = true;
                mThumbShape.setPosition(mousePos.x, mThumbShape.getPosition().y);
                notifyObservers();
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            mIsPressed = false;
        }
    }

    float getValue() const
    {
        float part = mThumbShape.getPosition().x - (mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.f);
        return (part / mTrackShape.getSize().x) * 100.f;
    }

    void addObserver(Observer* p)
    {
        mObservers.insert(p);
    }

    void removeObserver(Observer* p)
    {
        mObservers.erase(p);
    }

    void notifyObservers()
    {
        float val = getValue();
        for (auto obs : mObservers)
            obs->update(val);
    }
};

class Circle : public Observer, public Drawable
{
protected:
    sf::CircleShape mShape;
    sf::RenderWindow& mRenderWindow;

public:
    Circle(sf::RenderWindow& window, sf::Vector2f pos, float r)
        : mRenderWindow(window), mShape(r)
    {
        mShape.setOrigin(r, r);
        mShape.setPosition(pos);
        mShape.setFillColor(sf::Color::Green);
    }

    void draw() const override { mRenderWindow.draw(mShape); }
    void update(float value) override { mShape.setScale(value/50.f, value/50.f); }
};

class CircleColorChange : public Circle
{
public:
    CircleColorChange(sf::RenderWindow& window, sf::Vector2f pos, float r)
        : Circle(window, pos, r)
    {
        mShape.setFillColor(sf::Color(0,0,100));
    }

    void update(float value) override
    {
        mShape.setFillColor(sf::Color(0, 0, static_cast<sf::Uint8>(value*2)));
    }
};

class VerticalMover : public Observer, public Drawable
{
protected:
    sf::CircleShape mShape;
    sf::RenderWindow& mRenderWindow;
    float mMinY, mMaxY;

public:
    VerticalMover(sf::RenderWindow& window, sf::Vector2f pos, float r, float minY, float maxY)
        : mRenderWindow(window), mShape(r), mMinY(minY), mMaxY(maxY)
    {
        mShape.setOrigin(r,r);
        mShape.setPosition(pos);
        mShape.setFillColor(sf::Color::Yellow);
    }

    void draw() const override { mRenderWindow.draw(mShape); }
    void update(float value) override
    {
        float y = mMaxY - (value/100.f)*(mMaxY - mMinY);
        mShape.setPosition(mShape.getPosition().x, y);
    }
};

class Square : public Observer, public Drawable
{
protected:
    sf::RectangleShape mShape;
    sf::RenderWindow& mRenderWindow;

public:
    Square(sf::RenderWindow& window, sf::Vector2f pos, float size)
        : mRenderWindow(window), mShape({size,size})
    {
        mShape.setOrigin(size/2.f, size/2.f);
        mShape.setPosition(pos);
        mShape.setFillColor(sf::Color::Red);
    }

    void draw() const override { mRenderWindow.draw(mShape); }
    void update(float value) override { mShape.setRotation(3*value); }
};

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800,800), "Multiple Observers", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Slider slider(window, {400,500}, {500,20}, {25,90});
    std::vector<Observer*> observers;
    observers.push_back(new Circle(window,{100,300},50));
    observers.push_back(new Square(window,{400,300},100));
    observers.push_back(new CircleColorChange(window,{700,300},50));
    observers.push_back(new VerticalMover(window,{250,700},40,300,700));
    for(auto o:observers) slider.addObserver(o);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type==sf::Event::Closed) window.close();
            slider.handleEvent(e);
        }
        window.clear(sf::Color::Black);
        slider.draw();
        for(auto o:observers) dynamic_cast<Drawable*>(o)->draw();
        window.display();
    }

    for(auto o:observers) delete o;
}
