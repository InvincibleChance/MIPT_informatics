#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Rectangle");

    sf::RectangleShape rect(sf::Vector2f(200.f, 100.f));
    rect.setOrigin(rect.getSize() / 2.f);

    sf::View view(sf::FloatRect(0, 0, 600, 400));
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width / 2.f, event.size.height / 2.f);
                window.setView(view);
            }
        }

        rect.setPosition(view.getCenter());

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (rect.getGlobalBounds().contains(worldPos)) {
            rect.setFillColor(sf::Color::Red);
        } else {
            rect.setFillColor(sf::Color::Green);
        }

        window.clear();
        window.draw(rect);
        window.display();
    }
}
