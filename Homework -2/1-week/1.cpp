#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Вращающийся квадрат");
    sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
    square.setFillColor(sf::Color::Green);
    square.setOrigin(50.0f, 50.0f);
    square.setPosition(400.0f, 300.0f);
    float rotationSpeed = 50.0f;
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
        square.rotate(rotationSpeed * deltaTime);
        window.clear();
        window.draw(square);
        window.display();
    }
}
