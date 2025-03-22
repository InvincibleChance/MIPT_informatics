#include <SFML/Graphics.hpp>

int main() {
    int width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Движущийся круг");

    float radius = 30.f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(-radius, height / 2.f - radius);

    float speed = 5.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        circle.move(speed, 0);
        if (circle.getPosition().x - radius > width)
            circle.setPosition(-radius, height / 2.f - radius);

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();

        sf::sleep(sf::milliseconds(16));
    }
}