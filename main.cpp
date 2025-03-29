#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Базовый класс Draggable (тот же, что у вас в задаче)
class Draggable
{
private:
    sf::RenderWindow& mSfmlWindow;
    sf::RectangleShape mShape   {};
    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : mSfmlWindow(window)
    {
        mShape.setPosition(position);
        mShape.setSize(size);
        mShape.setFillColor(color);
    }

    // Делаем виртуальными, чтобы можно было переопределять в наследнике
    virtual bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mShape.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mShape.getPosition();
        }
        return mIsDragged;
    }

    virtual void onMouseReleased()
    {
        mIsDragged = false;
    }

    virtual void onMouseMoved(sf::Vector2f mousePosition)
    {
        if (mIsDragged)
        {
            mShape.setPosition(mousePosition - mOffset);
        }
    }

    void handleEvents(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMousePressed(mousePosition);
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMouseReleased();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }
    }

    // Сеттеры
    void setColor(sf::Color c)
    {
        mShape.setFillColor(c);
    }

    void setSize(sf::Vector2f sz)
    {
        mShape.setSize(sz);
    }

    void setPosition(sf::Vector2f p)
    {
        mShape.setPosition(p);
    }

    // Рисуем объект
    void draw() const
    {
        mSfmlWindow.draw(mShape);
    }
};

// Наследник, меняющий цвет при перетаскивании
class DraggableWithColorChange : public Draggable
{
private:
    sf::Color mBaseColor;
    sf::Color mDragColor;

public:
    // Конструктор с дополнительным параметром "цвет при перетаскивании"
    DraggableWithColorChange(sf::RenderWindow& window,
                             sf::Vector2f position,
                             sf::Vector2f size,
                             sf::Color baseColor,
                             sf::Color dragColor)
        : Draggable(window, position, size, baseColor)
        , mBaseColor(baseColor)
        , mDragColor(dragColor)
    {
    }

    // Переопределяем, чтобы менять цвет при нажатии (если попали в прямоугольник)
    bool onMousePressed(sf::Vector2f mousePosition) override
    {
        bool wasPressed = Draggable::onMousePressed(mousePosition);
        if (wasPressed)
        {
            // Меняем цвет на "dragColor"
            setColor(mDragColor);
        }
        return wasPressed;
    }

    // Переопределяем, чтобы вернуть исходный цвет при отпускании
    void onMouseReleased() override
    {
        Draggable::onMouseReleased();
        // Возвращаем "baseColor"
        setColor(mBaseColor);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DraggableWithColorChange");
    window.setFramerateLimit(60);

    // Пример использования DraggableWithColorChange:
    // baseColor = {80, 80, 120}, dragColor = {200, 100, 100}
    DraggableWithColorChange d{
        window,
        {100, 100},           // позиция
        {200, 400},           // размер
        sf::Color(80, 80, 120),   // исходный цвет (baseColor)
        sf::Color(200, 100, 100)  // цвет при перетаскивании (dragColor)
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обрабатываем события
            d.handleEvents(event);
        }

        window.clear(sf::Color::Black);

        // Рисуем объект
        d.draw();

        window.display();
    }
    return 0;
}
