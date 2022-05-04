#include <SFML/Graphics.hpp>


#include <stdlib.h>
#include <iostream>
#include <string>

#include "Ball.h"


int main()  
{
    auto w_size{ 800 };
    sf::RenderWindow window(sf::VideoMode(w_size,w_size), "Pong");

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text ltext;
    sf::Text rtext;

    int lscore = 0;
    ltext.setFont(font);
    ltext.setString(std::to_string(lscore));
    ltext.setCharacterSize(24);
    ltext.setFillColor(sf::Color::White);
  
    int rscore = 0;
    rtext.setFont(font);
    rtext.setString(std::to_string(rscore));
    rtext.setCharacterSize(24);
    rtext.setFillColor(sf::Color::White);
    rtext.setPosition((float)w_size - 15.f, 0.f); //Move text to right of window

    //Dimensions of paddles
    constexpr float len{ 10.f };
    constexpr float height{80.f};
    constexpr float paddle_speed{ 10.f };

    //Left paddle
    sf::RectangleShape board1(sf::Vector2f(len, height));
    board1.setPosition(0.f, 0.f);
    board1.setFillColor(sf::Color::White);
    board1.setOutlineColor(sf::Color::Black);
    board1.setOutlineThickness(-1.f);

    //Right paddle
    sf::RectangleShape board2(board1);
    board2.setPosition((float)w_size - len, 0.f);

    //Ball
    srand(time(NULL));
    Ball ball{ 10.f };
   

    while (window.isOpen())
    {
        window.setFramerateLimit(60); //Cap at 60fps


        auto ballBox = ball.getGlobalBounds();
        auto lPaddleBox= board1.getGlobalBounds();
        auto rPaddleBox = board2.getGlobalBounds();

        //Check collisions with paddles
        if (ballBox.intersects(lPaddleBox) || ballBox.intersects(rPaddleBox)) //Note that we check top left corner of paddle
        {
            ball.m_speed.x = -(1.2f)*ball.m_speed.x;
        }

        //Vertical collisions
        if (ball.getPosition().y < 0.f || ball.getPosition().y + 2*ball.getRadius() > w_size)
        {
            ball.m_speed.y = -ball.m_speed.y;
        }

        //Left player score a point
        if (ball.getPosition().x + 2 * ball.getRadius() > w_size)
        {
            ltext.setString(std::to_string(++lscore));
            ball.reset();
        }

        //Right player scores a point
        if (ball.getPosition().x <0)
        {
            rtext.setString(std::to_string(++rscore));
            if (rscore % 10 == 0) { rtext.move(-15.f, 0.f); } //Prevent part of score clipping outside window
            ball.reset();
        }

        ball.update();

        //Player 1 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && board1.getPosition().y > 0)
        {
            board1.move(0.f, -paddle_speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && board1.getPosition().y + height < w_size)
        {
            board1.move(0.f, paddle_speed);
        }


        //Player 2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && board2.getPosition().y > 0)
        {
            board2.move(0.f, -paddle_speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && board2.getPosition().y + height  < w_size)
        {
            board2.move(0.f, paddle_speed);
        }

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

        window.clear();
        window.draw(ball);
        window.draw(board1);
        window.draw(board2);
        window.draw(ltext);
        window.draw(rtext);
        window.display();
    }

    return 0;
}