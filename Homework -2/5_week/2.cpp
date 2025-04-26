#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <algorithm>

class Slider
{
public:
    using Callback = std::function<void(float)>;

    Slider(sf::RenderWindow& window, sf::Vector2f center, sf::Vector2f trackSize, sf::Vector2f thumbSize)
    : mWindow(window)
    {
        mTrack.setSize(trackSize);
        mTrack.setOrigin(trackSize / 2.f);
        mTrack.setPosition(center);
        mTrack.setFillColor({200,200,220});

        mThumb.setSize(thumbSize);
        mThumb.setOrigin(thumbSize / 2.f);
        mThumb.setPosition(center);
        mThumb.setFillColor({150,150,240});
    }

    void addCallback(Callback cb)
    {
        mCallbacks.push_back(std::move(cb));
    }

    void draw() const
    {
        mWindow.draw(mTrack);
        mWindow.draw(mThumb);
    }

    void handleEvent(const sf::Event& ev)
    {
        if (ev.type == sf::Event::MouseMoved && mPressed)
        {
            auto pos = mWindow.mapPixelToCoords({ev.mouseMove.x, ev.mouseMove.y});
            float minX = mTrack.getPosition().x - mTrack.getSize().x/2.f;
            float maxX = mTrack.getPosition().x + mTrack.getSize().x/2.f;
            float x = std::clamp(pos.x, minX, maxX);
            mThumb.setPosition(x, mThumb.getPosition().y);
            notify();
        }
        else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
        {
            auto pos = mWindow.mapPixelToCoords({ev.mouseButton.x, ev.mouseButton.y});
            if (mTrack.getGlobalBounds().contains(pos) || mThumb.getGlobalBounds().contains(pos))
            {
                mPressed = true;
                mThumb.setPosition(pos.x, mThumb.getPosition().y);
                notify();
            }
        }
        else if (ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Left)
        {
            mPressed = false;
        }
    }

    float getValue() const
    {
        float dx = mThumb.getPosition().x - (mTrack.getPosition().x - mTrack.getSize().x/2.f);
        return (dx / mTrack.getSize().x) * 100.f;
    }

private:
    void notify()
    {
        float v = getValue();
        for (auto& cb : mCallbacks)
            cb(v);
    }

    sf::RenderWindow& mWindow;
    sf::RectangleShape mTrack;
    sf::RectangleShape mThumb;
    bool mPressed = false;
    std::vector<Callback> mCallbacks;
};

int main()
{
    sf::ContextSettings cs; cs.antialiasingLevel = 8;
    sf::RenderWindow window({800,800}, "Two Sliders", sf::Style::Default, cs);
    window.setFramerateLimit(60);

    std::vector<sf::Shape*> shapes;
    shapes.push_back(new sf::CircleShape(50.f));
    shapes.back()->setOrigin(50.f,50.f);
    shapes.back()->setPosition(200,300);
    shapes.push_back(new sf::RectangleShape({100.f,100.f}));
    shapes.back()->setOrigin(50.f,50.f);
    shapes.back()->setPosition(400,300);
    shapes.push_back(new sf::CircleShape(40.f));
    shapes.back()->setOrigin(40.f,40.f);
    shapes.back()->setPosition(600,300);

    Slider sliderRot(window,{400,550},{500,20},{25,90});
    Slider sliderCol(window,{400,650},{500,20},{25,90});
    sliderRot.addCallback([&](float v){
        for(auto s: shapes)
            s->setRotation(v * 3.f);
    });
    sliderCol.addCallback([&](float v){
        sf::Uint8 c = static_cast<sf::Uint8>(v * 2);
        for(auto s: shapes)
            s->setFillColor({c, static_cast<sf::Uint8>(255-c), 150});
    });

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
            sliderRot.handleEvent(e);
            sliderCol.handleEvent(e);
        }
        window.clear({30,30,30});
        for(auto s: shapes)
            window.draw(*s);
        sliderRot.draw();
        sliderCol.draw();
        window.display();
    }

    for(auto p: shapes) delete p;
}
