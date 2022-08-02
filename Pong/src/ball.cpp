#include "ball.h"
#include <iostream>
Ball::Ball(float x, float y)
{
    m_shape_.setRadius(10.f);
    m_shape_.setFillColor(sf::Color::White);
    m_shape_.setOutlineColor(sf::Color::Black);
    m_shape_.setOrigin(m_shape_.getRadius(), m_shape_.getRadius()); //Set the origin to be the centre of the ball (rather than the default top-left)
    m_shape_.setPosition(x, y);
    m_shape_.setOutlineThickness(-1.f);

}


void Ball::Update(sf::RenderTarget& target)
{
    //Vertical collisions
    if (m_shape_.getPosition().y - m_shape_.getRadius() < 0.f || m_shape_.getPosition().y + m_shape_.getRadius() > target.getSize().y)
    {
        velocity.y = -velocity.y;
    }

    //If the ball collides with the right wall of the window, Left player scores a point
    if (m_shape_.getPosition().x + m_shape_.getRadius() > target.getSize().x)
    {
        //lscore.addPoint();
        Reset(0);
    }

    //If the ball collides with the left wall of the window, right player scores a point
    if (m_shape_.getPosition().x - m_shape_.getRadius() < 0)
    {
        //rscore.addPoint();
        //if (rscore.points % 10 == 0) { rscore.move(-15.f, 0.f); } //Prevent part of score clipping outside window
        Reset(1);
    }
    m_shape_.move(velocity);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape_);
}

//Reset ball to start position
void Ball::Reset(int start_dir)
{
    m_shape_.setPosition(300, 300);
    velocity.x = start_dir ? -5.f : 5.f; //Right player scores : Left player scores
    velocity.y = 0.f;
}


//Handles collisions between the ball and a paddle
void HandleCollisions(const Paddle& paddle, Ball& ball)
{
    if (ball.m_shape_.getGlobalBounds().intersects(paddle.m_shape_.getGlobalBounds()))
    {

        //ball.velocity.x *= -(1.1f); //If we just switch direction of velocity, the ball can get 'stuck' in the paddle. (uncomment this out to see!)

        //Update x velocity
        ball.velocity.x = (1.1f) * std::abs(ball.velocity.x); //Increase magnitude
        ball.velocity.x *= paddle.m_side_ == Paddle::Side::LEFT ? 1.f : -1.f; //Now decide direction

        ball.velocity.y = ball.m_shape_.getPosition().y < paddle.m_shape_.getPosition().y ? -5.f : 5.f;

    }
}