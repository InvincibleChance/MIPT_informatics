#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    const int width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Круг");

    const float radius = 30.f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);

    const float orbitRadius = 150.f;
    const sf::Vector2f center(width / 2.f, height / 2.f);

    float angle = 0.f;
    const float speed = 0.05f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float x = center.x + orbitRadius * std::cos(angle);
        float y = center.y + orbitRadius * std::sin(angle);
        circle.setPosition(x - radius, y - radius);

        angle += speed;

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();

        sf::sleep(sf::milliseconds(16));
    }
}