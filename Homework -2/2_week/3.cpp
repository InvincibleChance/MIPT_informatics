#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

sf::Color getRandomColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> d(0, 255);
    return sf::Color{d(gen), d(gen), d(gen)};
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circles");

    sf::View view = window.getDefaultView();
    window.setView(view);

    std::vector<sf::CircleShape> circles;
    const float radius = 20.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::Resized:
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width / 2.f, event.size.height / 2.f);
                    window.setView(view);
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePixelPos(event.mouseButton.x, event.mouseButton.y);
                        sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos);

                        sf::CircleShape circle(radius);
                        circle.setOrigin(radius, radius);
                        circle.setPosition(worldPos);
                        circle.setFillColor(sf::Color::White);
                        circles.push_back(circle);
                    }
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space) {
                        for (auto& circle : circles) {
                            circle.setFillColor(getRandomColor());
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);
        for (const auto& circle : circles) {
            window.draw(circle);
        }
        window.display();
    }
}
