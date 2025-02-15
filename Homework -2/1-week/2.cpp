#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;
    float charge;
};

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Симуляция шариков");
    window.setFramerateLimit(60);
    float dt = 1.0f / 60.0f;

    std::vector<Ball> balls;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int n = 2;
    for (int i = 0; i < n; i++) {
        Ball ball;
        float radius = 10.f;
        ball.shape = sf::CircleShape(radius);
        ball.shape.setOrigin(radius, radius);
        float posX = static_cast<float>(std::rand() % windowWidth);
        float posY = static_cast<float>(std::rand() % windowHeight);
        ball.shape.setPosition(posX, posY);

        ball.mass = 5.f + static_cast<float>(std::rand()) / RAND_MAX * 15.f;
        ball.charge = -10.f + static_cast<float>(std::rand()) / RAND_MAX * 20.f;
        if (std::abs(ball.charge) < 1.f)
            ball.charge = (ball.charge < 0 ? -1.f : 1.f);

        ball.shape.setFillColor(ball.charge >= 0 ? sf::Color::Red : sf::Color::Blue);
        ball.velocity = sf::Vector2f(0.f, 0.f);
        balls.push_back(ball);
    }

    float minDistance = 5.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Ball newBall;
                float radius = 10.f;
                newBall.shape = sf::CircleShape(radius);
                newBall.shape.setOrigin(radius, radius);
                newBall.shape.setPosition(mousePos);
                newBall.velocity = sf::Vector2f(0.f, 0.f);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    newBall.mass = 5.f;
                    newBall.charge = -10.f;
                    newBall.shape.setFillColor(sf::Color::Blue);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    newBall.mass = 30.f;
                    newBall.charge = 10.f;
                    newBall.shape.setFillColor(sf::Color::Red);
                }
                balls.push_back(newBall);
            }
        }

        std::vector<sf::Vector2f> accelerations(balls.size(), sf::Vector2f(0.f, 0.f));

        for (size_t i = 0; i < balls.size(); i++) {
            sf::Vector2f netForce(0.f, 0.f);
            sf::Vector2f pos_i = balls[i].shape.getPosition();
            for (size_t j = 0; j < balls.size(); j++) {
                if (i == j)
                    continue;
                sf::Vector2f pos_j = balls[j].shape.getPosition();
                sf::Vector2f r = pos_i - pos_j;
                float distance = std::sqrt(r.x * r.x + r.y * r.y);
                if (distance < minDistance)
                    continue;
                sf::Vector2f direction = r / distance;
                float forceMagnitude = (balls[i].charge * balls[j].charge) / distance;
                sf::Vector2f force = forceMagnitude * direction;
                netForce += force;
            }
            accelerations[i] = netForce / balls[i].mass;
        }

        for (size_t i = 0; i < balls.size(); i++) {
            balls[i].velocity += accelerations[i] * dt;
            sf::Vector2f pos = balls[i].shape.getPosition();
            pos += balls[i].velocity * dt;

            float radius = balls[i].shape.getRadius();
            if (pos.x - radius < 0.f) {
                pos.x = radius;
                balls[i].velocity.x = -balls[i].velocity.x;
            }
            if (pos.x + radius > windowWidth) {
                pos.x = windowWidth - radius;
                balls[i].velocity.x = -balls[i].velocity.x;
            }
            if (pos.y - radius < 0.f) {
                pos.y = radius;
                balls[i].velocity.y = -balls[i].velocity.y;
            }
            if (pos.y + radius > windowHeight) {
                pos.y = windowHeight - radius;
                balls[i].velocity.y = -balls[i].velocity.y;
            }
            balls[i].shape.setPosition(pos);
        }

        // Рисуем всё
        window.clear(sf::Color::Black);
        for (auto &ball : balls) {
            window.draw(ball.shape);
        }
        window.display();
    }
}
