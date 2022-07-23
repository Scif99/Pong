#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <iostream>
#include <string>

#include "ball.h"
#include "paddle.h"
#include "score.h"




int main()  
{
    sf::RenderWindow window(sf::VideoMode(800,500), "Pong");
    window.setFramerateLimit(60); //Cap at 60fps

    sf::Font font;
    font.loadFromFile("arial.ttf");
    Score lscore(font);
    Score rscore(font);
    lscore.setPosition((float)window.getSize().x/2 - 30.f, 0.f); //Move text to right of window
    rscore.setPosition((float)window.getSize().x/2 + 10.f, 0.f); //Move text to right of window

    Ball ball{ 10.f, window };
    Paddle lpaddle(20.f, 0.f, Paddle::Side::LEFT);
    Paddle rpaddle( window.getSize().x - 20.f, 0.f, Paddle::Side::RIGHT);


    //Game loop
    while (window.isOpen())
    {
        //Vertical collisions
        if (ball.getPosition().y - ball.getRadius() < 0.f || ball.getPosition().y + ball.getRadius() > window.getSize().y)
        {
            ball.velocity.y = -ball.velocity.y;
        }

        //If the ball collides with the right wall of the window, Left player scores a point
        if (ball.getPosition().x + ball.getRadius() > window.getSize().x)
        {
            lscore.addPoint();
            ball.reset(0);
        }

        //If the ball collides with the left wall of the window, right player scores a point
        if (ball.getPosition().x - ball.getRadius() <0)
        {
            rscore.addPoint();
            if (rscore.points % 10 == 0) { rscore.move(-15.f, 0.f); } //Prevent part of score clipping outside window
            ball.reset(1);
        }


        //Update game objects
        //TO-DO: Move collision detection after update?
        ball.update();
        lpaddle.update();
        rpaddle.update();

        handleCollisions(lpaddle, ball);
        handleCollisions(rpaddle, ball);

        //Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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