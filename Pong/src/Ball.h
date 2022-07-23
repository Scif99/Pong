#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"

struct Ball : public sf::CircleShape
{
    Ball(float radius, sf::RenderWindow& window)
        : sf::CircleShape{ radius } //Call constructor for sf::CircleShape
    {
        setPosition(window.getSize().x/2, window.getSize().y/2); //fix with window?
        setFillColor(sf::Color::White);
        setOutlineColor(sf::Color::Black);
        setOrigin(radius, radius); //Set the origin to be the centre of the ball (rather than the default top-left)
        setOutlineThickness(-1.f);
    }

    void reset(int start_dir);
    void update() { move(velocity); };
    void draw();
    sf::Vector2f velocity{5.f,5.f};
};

//Handles collisions between the ball and a paddle
void handleCollisions(const Paddle& paddle, Ball& ball)
{
    if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
    {
        ball.velocity.x *= -(1.1f); //X speed increased by fixed amount each hit
         
        //Ball hits top half of paddle
        if (paddle.getPosition().y > ball.getPosition().y )
        {
            ball.velocity.y = paddle.getPosition().y > ball.getPosition().y ? -5.f : 5.f;
        }


    }

}


//Reset ball to start position
void Ball::reset(int start_dir)
{
    setPosition(300, 300);
    velocity.x = start_dir? -5.f : 5.f; //Right player scores : Left player scores
    velocity.y = 0.f;
}
