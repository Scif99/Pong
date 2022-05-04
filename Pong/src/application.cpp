#include <SFML/Graphics.hpp>

#include <memory>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>



struct Ball
{
    Ball(float radius)
        :m_ball{ sf::CircleShape(radius) }, m_bound{sf::RectangleShape(sf::Vector2f(2*radius,2*radius))}
    {
        m_ball.setPosition(300, 300);
        m_bound.setPosition(300, 300);
        m_bound.setOutlineColor(sf::Color::Red);
        speed.x = (rand() % 10) -5;
        speed.y = (rand() % 10) -5;
    }
    
    void update(const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2, int w_size);
    void reset(); 
    sf::CircleShape m_ball;
    sf::Vector2f speed;
    sf::RectangleShape m_bound; //bounding box


};



//Does the ball collide with any of the paddles?
bool checkCollides(Ball& b, const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2, int w_size)
{
    //Left paddle
    if (b.m_bound.getPosition().x < paddle1.getPosition().x + paddle1.getSize().x
        && b.m_bound.getPosition().y + b.m_bound.getSize().y > paddle1.getPosition().y
        && b.m_bound.getPosition().y < paddle1.getPosition().y + paddle1.getSize().y)
        return true;

    else if (b.m_bound.getPosition().x + b.m_bound.getSize().x > paddle2.getPosition().x
        && b.m_bound.getPosition().y + b.m_bound.getSize().y > paddle2.getPosition().y
        && b.m_bound.getPosition().y < paddle2.getPosition().y + paddle2.getSize().y)
        return true;

    else return false;

}

void Ball::update(const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2, int w_size)
{
    auto pos = m_bound.getPosition();

    //Vertical collisions
    if (pos.y < 0 || pos.y + m_bound.getSize().y> w_size)
    {
        speed.y = -speed.y;
    }

    //Horizontal collisions
    if (checkCollides(*this, paddle1, paddle2, w_size)) speed.x = -speed.x;


    m_bound.setPosition(pos.x + speed.x, pos.y + speed.y);
    m_ball.setPosition(pos.x + speed.x, pos.y + speed.y);
}

void Ball::reset()
{
    m_ball.setPosition(300, 300);
    m_bound.setPosition(300, 300);
    speed.x = (rand() % 10) - 5;
    speed.y = (rand() % 10) - 5;
}


int main()
{
    constexpr int w_size{ 800 };
    sf::RenderWindow window(sf::VideoMode(w_size,w_size), "Pong");

    //Dimensions of paddles
    float  len{ 10.f };
    float height{60.f};
    float paddle_speed = 10.f;

    //Left paddle
    sf::RectangleShape board1(sf::Vector2f(len, height));
    board1.setPosition(0.f, 0.f);
    board1.setFillColor(sf::Color::White);
    board1.setOutlineColor(sf::Color::Black);
    board1.setOutlineThickness(-1.f);


    //Right paddle
    sf::RectangleShape board2(sf::Vector2f(len, height));
    board2.setPosition(w_size - len, 0.f);
    board2.setFillColor(sf::Color::White);
    board2.setOutlineColor(sf::Color::Black);
    board2.setOutlineThickness(-1.f);

    //Ball
    srand(time(NULL));
    std::unique_ptr<Ball> pball = std::make_unique<Ball>(10.f);
   
    sf::Clock clock;
    while (window.isOpen())
    {
        pball->update(board1,board2, w_size);


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

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    srand(time(NULL));
                    pball->reset();
                }
                else if (event.key.code == sf::Keyboard::E)
                {
                    pball->speed = pball->speed * 1.2f;   
                }
            }
        }

        window.clear();
        window.draw(board1);
        window.draw(board2);
        window.draw(pball->m_ball);
        window.display();
    }

    return 0;
}