#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Score
{
	Score() {};

private:
	std::string m_name_;
	unsigned short m_score_;
};