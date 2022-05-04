#pragma once
#include <SFML/Graphics.hpp>

struct Ball : public sf::CircleShape
{
    Ball(float radius)
        : sf::CircleShape{ radius } //Call constructor for sf::CircleShape
    {
        setPosition(300, 300);
        setFillColor(sf::Color::White);
        setOutlineColor(sf::Color::Black);
        setOutlineThickness(-1.f);
        m_speed.x = (rand() % 10) - 5;
        m_speed.y = (rand() % 10) - 5;
    }

    void reset();
    sf::Vector2f m_speed;
};

//Reset ball to start position
void Ball::reset()
{
    setPosition(300, 300);
    m_speed.x = (rand() % 10) - 5;
    m_speed.y = (rand() % 10) - 5;
}
