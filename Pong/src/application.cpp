#include <SFML/Graphics.hpp>


#include <iostream>
#include <string>

#include "ball.h"
#include "paddle.h"
#include "score.h"




int main()  
{
    sf::RenderWindow window(sf::VideoMode(800,500), "Pong");

    sf::Font font;
    font.loadFromFile("arial.ttf");
    Score lscore(font);
    Score rscore(font);
    lscore.setPosition((float)window.getSize().x/2 - 30.f, 0.f); //Move text to right of window
    rscore.setPosition((float)window.getSize().x/2 + 10.f, 0.f); //Move text to right of window

    Paddle lpaddle( sf::Vector2f(20.f,80.f ),20.f,0.f);
    Paddle rpaddle(sf::Vector2f(20.f, 80.f), window.getSize().x - 2*20.f, 0.f);

    //Ball
    Ball ball{ 10.f, window };
   

    while (window.isOpen())
    {
        window.setFramerateLimit(60); //Cap at 60fps

        //Check collisions with paddles
        if (ball.getGlobalBounds().intersects(lpaddle.getGlobalBounds()) 
            || ball.getGlobalBounds().intersects(rpaddle.getGlobalBounds()))
        {
            auto centre_y_ball = ball.getPosition().y + ball.getRadius(); //y coordinate of centre of ball

            //get y coordinate of the centre of the paddle hit.
            auto centre_y_pad = ball.getGlobalBounds().intersects(lpaddle.getGlobalBounds()) ?
                lpaddle.getPosition().y + lpaddle.getSize().y / 2 : rpaddle.getPosition().y + rpaddle.getSize().y / 2;

            auto d = centre_y_pad - centre_y_ball;
            auto scale = lpaddle.getSize().y / 2;
            auto v = std::fabs(d) / scale; //New speed scales depending on y-distance between ball and paddle

            ball.m_speed.x *= -(1.1f); //X speed increased by fixed amount each hit

            if (ball.m_speed.y >= 0)
            {
                if (d < 0)
                {
                    ball.m_speed.y += (2 * v) + 2.f; //Case 1
                }

                if (d > 0)
                {
                    ball.m_speed.y = -ball.m_speed.y - 2.f ; //Case 4

                }
                
            }

            else if (ball.m_speed.y < 0)
            {
                if (d < 0)
                {
                    ball.m_speed.y = -ball.m_speed.y  + 2.f; //Case 3
                }

                if (d > 0)
                {
                    ball.m_speed.y -= (2 * v) -2.f; //Case 2
                }
            }



        }

        //Vertical collisions
        if (ball.getPosition().y < 0.f || ball.getPosition().y + 2*ball.getRadius() > window.getSize().y)
        {
            ball.m_speed.y = -ball.m_speed.y;
        }

        //Left player score a point
        if (ball.getPosition().x + 2 * ball.getRadius() > window.getSize().x)
        {
            lscore.addPoint();
            ball.reset(0);
        }

        //Right player scores a point
        if (ball.getPosition().x <0)
        {
            rscore.addPoint();
            if (rscore.points % 10 == 0) { rscore.move(-15.f, 0.f); } //Prevent part of score clipping outside window
            ball.reset(1);
        }

        //Update game objects
        ball.setPosition(ball.getPosition().x + ball.m_speed.x, ball.getPosition().y + ball.m_speed.y);

        //Left Paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && lpaddle.getPosition().y > 0)
        {
            lpaddle.move(0.f, -lpaddle.speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && lpaddle.getPosition().y + lpaddle.getSize().y < window.getSize().y)
        {
            lpaddle.move(0.f, lpaddle.speed);
        }

        //Right Paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rpaddle.getPosition().y > 0)
        {
            rpaddle.move(0.f, -rpaddle.speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rpaddle.getPosition().y + rpaddle.getSize().y < window.getSize().y)
        {
            rpaddle.move(0.f, rpaddle.speed);
        }

        //Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Press space to manually reset
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {

                window.close();
            }
        }

        //Render
        window.clear();
        window.draw(ball);
        window.draw(lpaddle);
        window.draw(rpaddle);
        window.draw(rscore);
        window.draw(lscore);

        //Swap buffers
        window.display();
    }
    return 0;
}