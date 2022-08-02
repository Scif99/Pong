#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"


class Ball : sf::Drawable
{
public:
    Ball(float x, float y);

    void Reset(int start_dir);
    void Update(sf::RenderTarget& target);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
    friend void HandleCollisions(const Paddle& paddle, Ball& ball);
    void setPosition(float x, float y) { m_shape_.setPosition(x, y); }
private:
    sf::Vector2f velocity{-5.f,5.f };
    sf::CircleShape m_shape_;
};

