#include <SFML/Graphics.hpp>


#include <stdlib.h>
#include <iostream>
#include <string>

#include "ball.h"
#include "paddle.h"
#include "score.h"


int main()  
{
    sf::RenderWindow window(sf::VideoMode(800,800), "Pong");

    sf::Font font;
    font.loadFromFile("arial.ttf");
    Score lscore(font);
    Score rscore(font);
    rscore.setPosition((float)window.getSize().x - 15.f, 0.f); //Move text to right of window

    Paddle lpaddle( sf::Vector2f(10.f,80.f ),0.f,0.f);
    Paddle rpaddle(sf::Vector2f(10.f, 80.f), window.getSize().x - 10.f, 0.f);

    //Ball
    srand(time(NULL));
    Ball ball{ 10.f };
   

    while (window.isOpen())
    {
        window.setFramerateLimit(60); //Cap at 60fps

        //Check collisions with paddles
        if (ball.getGlobalBounds().intersects(lpaddle.getGlobalBounds()) 
            || ball.getGlobalBounds().intersects(rpaddle.getGlobalBounds()))
        {
            ball.m_speed.x = -(1.2f)*ball.m_speed.x;
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
            ball.reset();
        }

        //Right player scores a point
        if (ball.getPosition().x <0)
        {
            rscore.addPoint();
            if (rscore.points % 10 == 0) { rscore.move(-15.f, 0.f); } //Prevent part of score clipping outside window
            ball.reset();
        }

        //Update game objects
        ball.setPosition(ball.getPosition().x + ball.m_speed.x, ball.getPosition().y + ball.m_speed.y);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && lpaddle.getPosition().y > 0)
        {
            lpaddle.move(0.f, -lpaddle.speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && lpaddle.getPosition().y + lpaddle.getSize().y < window.getSize().y)
        {
            lpaddle.move(0.f, lpaddle.speed);
        }

        //Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Press space to manually reset
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                srand(time(NULL));
                ball.reset();
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