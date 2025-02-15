#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>


float distance(sf::Vector2f start, sf::Vector2f finish)
{
    return std::sqrt((start.x - finish.x)*(start.x - finish.x) +
                     (start.y - finish.y)*(start.y - finish.y));
}


void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = { sf::Vertex(start, color), sf::Vertex(finish, color) };
    window.draw(line_vertices, 2, sf::Lines);
}


struct Ball
{
    sf::Vector2f position;
    float radius;
    bool isChoosen;
    sf::Color color;

    Ball(sf::Vector2f position, float radius) : position(position), radius(radius)
    {
        isChoosen = false;
        color = sf::Color::White;
    }

    void draw(sf::RenderWindow& window) const
    {
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setOrigin(radius, radius);
        circle.setPosition(position);
        window.draw(circle);

        if (isChoosen)
        {
            const float fraction = 0.7f;
            drawLine(window, { position.x - radius, position.y + radius }, { position.x - radius, position.y + radius * fraction });
            drawLine(window, { position.x - radius, position.y + radius }, { position.x - fraction * radius, position.y + radius });

            drawLine(window, { position.x + radius, position.y + radius }, { position.x + radius, position.y + radius * fraction });
            drawLine(window, { position.x + radius, position.y + radius }, { position.x + radius * fraction, position.y + radius });

            drawLine(window, { position.x + radius, position.y - radius }, { position.x + radius * fraction, position.y - radius });
            drawLine(window, { position.x + radius, position.y - radius }, { position.x + radius, position.y - radius * fraction });

            drawLine(window, { position.x - radius, position.y - radius }, { position.x - radius * fraction, position.y - radius });
            drawLine(window, { position.x - radius, position.y - radius }, { position.x - radius, position.y - radius * fraction });
        }
    }
};

sf::Color randomColor()
{
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    std::list<Ball> balls;
    balls.push_back(Ball({200, 200}, 26));
    balls.push_back(Ball({400, 300}, 20));
    balls.push_back(Ball({500, 100}, 16));
    balls.push_back(Ball({200, 400}, 18));
    balls.push_back(Ball({350, 150}, 22));
    balls.push_back(Ball({750, 400}, 21));

    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    selectionRect.setOutlineThickness(1);

    bool isSelecting = false;
    sf::Vector2f selectionStart;

    bool isDragging = false;
    sf::Vector2f lastMousePos;

    bool showContextMenu = false;
    sf::Vector2f contextMenuPos;
    std::vector<std::string> contextMenuOptions = {"Delete", "Create", "Random Color", "Increase", "Decrease", "Copy", "Paste", "Cut"};

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Не удалось загрузить шрифт arial.ttf. Контекстное меню может не отображаться." << std::endl;
    }

    std::list<Ball> clipboard;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

                if (isSelecting)
                {
                    sf::Vector2f size = mousePos - selectionStart;
                    sf::Vector2f rectPos(std::min(selectionStart.x, mousePos.x), std::min(selectionStart.y, mousePos.y));
                    selectionRect.setPosition(rectPos);
                    selectionRect.setSize({ std::abs(size.x), std::abs(size.y) });

                    sf::FloatRect selRect(rectPos, selectionRect.getSize());
                    for (Ball& b : balls)
                    {
                        sf::FloatRect ballRect(b.position.x - b.radius, b.position.y - b.radius, 2 * b.radius, 2 * b.radius);
                        if (selRect.contains(ballRect.left, ballRect.top) &&
                            selRect.contains(ballRect.left + ballRect.width, ballRect.top + ballRect.height))
                        {
                            b.isChoosen = true;
                        }
                        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        {
                            b.isChoosen = false;
                        }
                    }
                }
                if (isDragging)
                {
                    sf::Vector2f delta = mousePos - lastMousePos;
                    for (Ball& b : balls)
                    {
                        if (b.isChoosen)
                            b.position += delta;
                    }
                    lastMousePos = mousePos;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    showContextMenu = true;
                    contextMenuPos = mousePos;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool clickedOnBall = false;
                    for (Ball& b : balls)
                    {
                        if (distance(mousePos, b.position) <= b.radius)
                        {
                            clickedOnBall = true;
                            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                            {
                                for (Ball& b2 : balls)
                                    b2.isChoosen = false;
                            }
                            b.isChoosen = true;
                            isDragging = true;
                            lastMousePos = mousePos;
                            break;
                        }
                    }
                    if (!clickedOnBall)
                    {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        {
                            for (Ball& b : balls)
                                b.isChoosen = false;
                        }
                        isSelecting = true;
                        selectionStart = mousePos;
                        selectionRect.setPosition(mousePos);
                        selectionRect.setSize({ 0, 0 });
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                    {
                        float newRadius = 5 + rand() % 40;
                        Ball newBall(mousePos, newRadius);
                        newBall.color = randomColor();
                        balls.push_back(newBall);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isSelecting = false;
                    isDragging = false;
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    for (Ball& b : balls)
                    {
                        if (b.isChoosen)
                            b.color = randomColor();
                    }
                }

                if (event.key.code == sf::Keyboard::Delete)
                {
                    for (auto it = balls.begin(); it != balls.end(); )
                    {
                        if (it->isChoosen)
                            it = balls.erase(it);
                        else
                            ++it;
                    }
                }
                if (event.key.code == sf::Keyboard::C && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    clipboard.clear();
                    for (const Ball& b : balls)
                    {
                        if (b.isChoosen)
                            clipboard.push_back(b);
                    }
                }
                if (event.key.code == sf::Keyboard::V && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    for (Ball& b : clipboard)
                    {
                        Ball copy = b;
                        copy.position += sf::Vector2f(10, 10);
                        copy.isChoosen = false;
                        balls.push_back(copy);
                    }
                }
                if (event.key.code == sf::Keyboard::X && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    clipboard.clear();
                    for (auto it = balls.begin(); it != balls.end(); )
                    {
                        if (it->isChoosen)
                        {
                            clipboard.push_back(*it);
                            it = balls.erase(it);
                        }
                        else
                            ++it;
                    }
                }
            }
        }

        if (showContextMenu)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                int optionIndex = static_cast<int>((mousePos.y - contextMenuPos.y) / 20);
                if (optionIndex >= 0 && optionIndex < static_cast<int>(contextMenuOptions.size()))
                {
                    std::string option = contextMenuOptions[optionIndex];
                    if (option == "Delete")
                    {
                        for (auto it = balls.begin(); it != balls.end(); )
                        {
                            if (it->isChoosen)
                                it = balls.erase(it);
                            else
                                ++it;
                        }
                    }
                    else if (option == "Create")
                    {
                        float newRadius = 5 + rand() % 40;
                        Ball newBall(contextMenuPos, newRadius);
                        newBall.color = randomColor();
                        balls.push_back(newBall);
                    }
                    else if (option == "Random Color")
                    {
                        for (Ball& b : balls)
                        {
                            if (b.isChoosen)
                                b.color = randomColor();
                        }
                    }
                    else if (option == "Increase")
                    {
                        for (Ball& b : balls)
                        {
                            if (b.isChoosen)
                                b.radius *= 1.25f;
                        }
                    }
                    else if (option == "Decrease")
                    {
                        for (Ball& b : balls)
                        {
                            if (b.isChoosen)
                                b.radius *= 0.75f;
                        }
                    }
                    else if (option == "Copy")
                    {
                        clipboard.clear();
                        for (const Ball& b : balls)
                        {
                            if (b.isChoosen)
                                clipboard.push_back(b);
                        }
                    }
                    else if (option == "Paste")
                    {
                        for (Ball& b : clipboard)
                        {
                            Ball copy = b;
                            copy.position += sf::Vector2f(10, 10);
                            copy.isChoosen = false;
                            balls.push_back(copy);
                        }
                    }
                    else if (option == "Cut")
                    {
                        clipboard.clear();
                        for (auto it = balls.begin(); it != balls.end(); )
                        {
                            if (it->isChoosen)
                            {
                                clipboard.push_back(*it);
                                it = balls.erase(it);
                            }
                            else
                                ++it;
                        }
                    }
                    showContextMenu = false;
                }
            }
        }

        window.clear(sf::Color::Black);
        for (Ball& b : balls)
            b.draw(window);
        if (isSelecting)
            window.draw(selectionRect);

        if (showContextMenu)
        {
            for (size_t i = 0; i < contextMenuOptions.size(); i++)
            {
                sf::RectangleShape optionRect;
                optionRect.setPosition(contextMenuPos.x, contextMenuPos.y + i * 20);
                optionRect.setSize({ 100, 20 });
                optionRect.setFillColor(sf::Color(100, 100, 100, 200));
                optionRect.setOutlineColor(sf::Color::White);
                optionRect.setOutlineThickness(1);
                window.draw(optionRect);
                if (!font.getInfo().family.empty())
                {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(contextMenuOptions[i]);
                    text.setCharacterSize(14);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(contextMenuPos.x + 5, contextMenuPos.y + i * 20);
                    window.draw(text);
                }
            }
        }

        window.display();
    }

}
