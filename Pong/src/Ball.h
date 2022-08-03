#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"


class Ball : sf::Drawable
{
public:
    Ball(float x, float y);

    void Reset(int start_dir);
    //void Update(sf::RenderTarget& target);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
    friend void HandleCollisions(const Paddle& paddle, Ball& ball);

    void setPosition(float x, float y) { m_shape_.setPosition(x, y); }
    sf::Vector2f getPosition() const { return m_shape_.getPosition(); }
    void move(const sf::Vector2f& v) { m_shape_.move(v); }

    float getRadius() const { return m_shape_.getRadius(); }

    void setVelocity(float x, float y) { m_velocity_.x = x, m_velocity_.y = y; }
    sf::Vector2f velocity() const { return m_velocity_; }

private:
    sf::Vector2f m_velocity_{-5.f,5.f };
    sf::CircleShape m_shape_;
};

