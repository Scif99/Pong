#pragma once
#include <SFML/Graphics.hpp>

struct Score : sf::Text
{
	Score(const sf::Font& f)
		: sf::Text()
	{
		setFont(f);
		setString(std::to_string(points));
		setCharacterSize(40);
		setFillColor(sf::Color::White);
	}

	void addPoint() { setString(std::to_string(++points)); }
	int points = 0;

};