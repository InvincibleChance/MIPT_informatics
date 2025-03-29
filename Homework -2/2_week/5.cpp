#include <SFML/Graphics.hpp>
#include "slider.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "RGB Circle");
    window.setFramerateLimit(60);

    Slider sliderR(window, {150, 150}, {300, 10}, {15, 40});
    Slider sliderG(window, {150, 250}, {300, 10}, {15, 40});
    Slider sliderB(window, {150, 350}, {300, 10}, {15, 40});

    sf::CircleShape circle(100.f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(600, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            sliderR.handleEvent(event);
            sliderG.handleEvent(event);
            sliderB.handleEvent(event);
        }

        sf::Color color(
            static_cast<sf::Uint8>(sliderR.getValue() * 2.55f),  // 0–100 → 0–255
            static_cast<sf::Uint8>(sliderG.getValue() * 2.55f),
            static_cast<sf::Uint8>(sliderB.getValue() * 2.55f)
        );
        circle.setFillColor(color);

        window.clear(sf::Color::White);
        sliderR.draw();
        sliderG.draw();
        sliderB.draw();
        window.draw(circle);
        window.display();
    }
}
