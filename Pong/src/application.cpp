#include <SFML/Graphics.hpp>
#include "ball.h"
#include <memory>


bool in_bounds(const sf::Vector2f& pos, const sf::CircleShape& ball)
{
    return true;
}



int main()
{
    constexpr int w_size{ 800 };
    sf::RenderWindow window(sf::VideoMode(w_size,w_size), "Pong");

    float  len{ 20.f };
    float height{50.f};
    sf::RectangleShape board1(sf::Vector2f(len, height));
    board1.setPosition(0.f, 0.f);
    board1.setFillColor(sf::Color::Green);


    sf::RectangleShape board2(sf::Vector2f(len, height));
    board2.setPosition(w_size - 20.f, 0.f);
    board2.setFillColor(sf::Color::Red);


    std::unique_ptr<Ball> pball{ std::make_unique<Ball>(30.f) };



    while (window.isOpen())
    {
        //Player 1 movement

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            auto pos = board1.getPosition();
            if (pos.y - 0.2f > 0)
            {
                board1.setPosition(pos + sf::Vector2f(0.f, -0.2f));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            auto pos = board1.getPosition();
            if (pos.y  + height + 0.2f < w_size)
            {
                board1.setPosition(pos + sf::Vector2f(0.f, 0.2f));
            }
           
        }


        //Player 2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            auto pos = board2.getPosition();
            if (pos.y - 0.2f > 0)
            {
                board2.setPosition(pos + sf::Vector2f(0.f, -0.2f));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            auto pos = board2.getPosition();
            if (pos.y + height + 0.2f < w_size)
            {
                board2.setPosition(pos + sf::Vector2f(0.f, 0.2f));
            }

        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }





        window.clear();
        window.draw(board1);
        window.draw(board2);
        window.display();
    }

    return 0;
}