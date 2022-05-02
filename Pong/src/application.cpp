#include <SFML/Graphics.hpp>

#include <memory>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>

struct Ball
{
    Ball(float radius)
        :m_ball{ sf::CircleShape(radius) }, m_bound{sf::RectangleShape(sf::Vector2f(2*radius,2*radius))}
    {
        m_ball.setPosition(300, 300);
        speed.x = (rand() % 10) -5;
        speed.y = (rand() % 10) -5;
    }
    
    void update();
    
    sf::CircleShape m_ball;
    sf::Vector2f speed;
    sf::RectangleShape m_bound; //bounding box


};

void Ball::update()
{
    auto pos = m_ball.getPosition();


    m_ball.setPosition(pos.x + speed.x, pos.y + speed.y);
}

bool in_bounds(const sf::Vector2f& pos, const sf::CircleShape& ball)
{
    return true;
}






int main()
{
    constexpr int w_size{ 800 };
    sf::RenderWindow window(sf::VideoMode(w_size,w_size), "Pong");

    //Dimensions of paddles
    float  len{ 20.f };
    float height{50.f};
    float paddle_speed = 10.f;

    //Left paddle
    sf::RectangleShape board1(sf::Vector2f(len, height));
    board1.setPosition(0.f, 0.f);
    board1.setFillColor(sf::Color::White);
    board1.setOutlineColor(sf::Color::Black);
    board1.setOutlineThickness(-1.f);


    //Right paddle
    sf::RectangleShape board2(sf::Vector2f(len, height));
    board2.setPosition(w_size - 20.f, 0.f);
    board2.setFillColor(sf::Color::White);
    board1.setOutlineColor(sf::Color::Black);
    board1.setOutlineThickness(-1.f);

    //Ball
    std::unique_ptr<Ball> pball{ std::make_unique<Ball>(10.f) };


    sf::Clock clock;
    while (window.isOpen())
    {

        pball->update();
        sf::Time elapsed = clock.getElapsedTime();
        std::cout << 1/elapsed.asSeconds() << '\n';
        window.setFramerateLimit(60);

        clock.restart();
        //Player 1 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            auto pos = board1.getPosition();
            if (pos.y> 0)
            {
                board1.setPosition(pos + sf::Vector2f(0.f, -paddle_speed));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            auto pos = board1.getPosition();
            if (pos.y  + height< w_size)
            {
                board1.setPosition(pos + sf::Vector2f(0.f, paddle_speed));
            }
           
        }


        //Player 2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            auto pos = board2.getPosition();
            if (pos.y > 0)
            {
                board2.setPosition(pos + sf::Vector2f(0.f, -paddle_speed));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            auto pos = board2.getPosition();
            if (pos.y + height < w_size)
            {
                board2.setPosition(pos + sf::Vector2f(0.f, paddle_speed));
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
        window.draw(pball->m_ball);
        window.display();
    }

    return 0;
}