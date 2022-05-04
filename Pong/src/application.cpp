#include <SFML/Graphics.hpp>

#include <memory>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>



struct Ball : public sf::CircleShape
{
    Ball(float radius)
        : sf::CircleShape{ radius } //Call constructor for sf::CircleShape
    {
        setPosition(300, 300);
        setFillColor(sf::Color::White);
        setOutlineColor(sf::Color::Black);
        setOutlineThickness(-1.f);
        m_speed.x = (rand() % 10) -5;
        m_speed.y = (rand() % 10) -5;
    }
    void update() { setPosition(getPosition().x + m_speed.x, getPosition().y + m_speed.y); }
    void reset();
    sf::Vector2f m_speed;
};

//Reset ball to start position
void Ball::reset()
{
    setPosition(300, 300);
    m_speed.x = (rand() % 10) - 5;
    m_speed.y = (rand() % 10) - 5;
}

int main()
{
    auto w_size{ 800 };
    sf::RenderWindow window(sf::VideoMode(w_size,w_size), "Pong");

    //Dimensions of paddles
    constexpr float len{ 10.f };
    constexpr float height{60.f};
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
   
    //Initialise clock
    sf::Clock clock;

    while (window.isOpen())
    {
        window.setFramerateLimit(60); //Cap at 60fps


        auto ballBox = ball.getGlobalBounds();
        auto lPaddleBox= board1.getGlobalBounds();
        auto rPaddleBox = board2.getGlobalBounds();

        //Check collisions with paddles
        if (ballBox.intersects(lPaddleBox) || ballBox.intersects(rPaddleBox)) //Note that we check top left corner of paddle
        {
            ball.m_speed.x = -ball.m_speed.x;
        }

        //Vertical collisions
        if (ball.getPosition().y < 0.f || ball.getPosition().y + 2*ball.getRadius() > w_size)
        {
            ball.m_speed.y = -ball.m_speed.y;
        }

        //Rset ball if it goes out of bounds horizontally
        if (ball.getPosition().x <0 || ball.getPosition().x + 2*ball.getRadius() > w_size)
        {
            ball.reset();
        }

        //Increase speed of ball every 5 seconds
        auto x = clock.getElapsedTime().asSeconds();
        if (x >= 5)
        {
            ball.m_speed *= 1.2f;
            clock.restart();
        }

        ball.update();

        //Player 1 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && board1.getPosition().y > 0)
        {
            board1.setPosition(board1.getPosition() + sf::Vector2f(0.f, -paddle_speed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && board1.getPosition().y + height < w_size)
        {
            board1.setPosition(board1.getPosition() + sf::Vector2f(0.f, paddle_speed));
        }


        //Player 2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && board2.getPosition().y > 0)
        {
            board2.setPosition(board2.getPosition() + sf::Vector2f(0.f, -paddle_speed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && board2.getPosition().y + height  < w_size)
        {
            board2.setPosition(board2.getPosition() + sf::Vector2f(0.f, paddle_speed));
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
        window.display();
    }

    return 0;
}