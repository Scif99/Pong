#pragma once
#include <SFML/Graphics.hpp>

struct Paddle : sf::RectangleShape
{
	Paddle(const sf::Vector2f& sz, float x, float y)
		:sf::RectangleShape(sz)
	{
		setPosition(x, y);
		setFillColor(sf::Color::White);
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(-1.f);
	}

	float speed{ 10.f };
};
