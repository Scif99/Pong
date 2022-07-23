#pragma once
#include <SFML/Graphics.hpp>

struct Paddle : sf::RectangleShape
{
	enum class Side 
	{
		LEFT,
		RIGHT
	};
	Paddle(float x, float y, Side side)
		:side{side}
	{

		setSize(dim);
		setPosition(x, +dim.y/2);
		setFillColor(sf::Color::White);
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(-1.f);
		setOrigin(dim.x/2,dim.y/2);
	}

	void handleInput();
	void update();


	sf::Vector2f dim{ 20.f,80.f };
	sf::Vector2f velocity;
	Side side;
};

constexpr float w_height{ 500.f };
void Paddle::handleInput()
{
	//Get correct key codes
	sf::Keyboard::Key up_key = side == Paddle::Side::LEFT ? sf::Keyboard::W : sf::Keyboard::Up;
	sf::Keyboard::Key down_key = side == Paddle::Side::LEFT ? sf::Keyboard::S : sf::Keyboard::Down;

	if (sf::Keyboard::isKeyPressed(up_key) && getPosition().y - getSize().y/2 > 0)
	{
		velocity.y = -10.f;
	}
	else if (sf::Keyboard::isKeyPressed(down_key) && getPosition().y + getSize().y/2 < w_height)
	{
		velocity.y = 10.f;
	}
	else { velocity.y = 0.f; }
}



void Paddle::update()
{
	handleInput();
	move(velocity);
}

