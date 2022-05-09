#pragma once
#include <SFML/Graphics.hpp>

struct Ball : public sf::CircleShape
{
    Ball(float radius, sf::Window& window)
        : sf::CircleShape{ radius } //Call constructor for sf::CircleShape
    {
        setPosition(window.getSize().x/2, window.getSize().y/2); //fix with window?
        setFillColor(sf::Color::White);
        setOutlineColor(sf::Color::Black);
        setOutlineThickness(-1.f);
        m_speed.x = 5.f;
        m_speed.y = 0.f;
    }

    void reset(int start_dir);
    sf::Vector2f m_speed;
};

//Reset ball to start position
void Ball::reset(int start_dir)
{
    setPosition(300, 300);
    m_speed.x = start_dir? -5.f : 5.f; //Right player scores : Left player scores
    m_speed.y = 0.f;
}
