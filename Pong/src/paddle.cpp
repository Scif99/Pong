#include "paddle.h"

Paddle::Paddle(float x, float y, Side side)
	:m_side_{ side }
{

	m_shape_.setSize(m_dim_);
	m_shape_.setPosition(x, m_dim_.y / 2);
	m_shape_.setFillColor(sf::Color::White);
	m_shape_.setOutlineColor(sf::Color::Black);
	m_shape_.setOutlineThickness(-1.f);
	m_shape_.setOrigin(m_dim_.x / 2, m_dim_.y / 2);
}


//void Paddle::HandleInput(const sf::RenderWindow& window)
//{
//	//Get correct key codes
//	sf::Keyboard::Key up_key = m_side_ == Paddle::Side::LEFT ? sf::Keyboard::W : sf::Keyboard::Up;
//	sf::Keyboard::Key down_key = m_side_ == Paddle::Side::LEFT ? sf::Keyboard::S : sf::Keyboard::Down;
//
//	if (sf::Keyboard::isKeyPressed(up_key) && m_shape_.getPosition().y - m_shape_.getSize().y / 2 > 0)
//	{
//		m_velocity_.y = -10.f;
//	}
//	else if (sf::Keyboard::isKeyPressed(down_key) && m_shape_.getPosition().y + m_shape_.getSize().y / 2 < window.getSize().y)
//	{
//		m_velocity_.y = 10.f;
//	}
//	else { m_velocity_.y = 0.f; }
//}



void Paddle::Update()
{
	m_shape_.move(m_velocity_);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape_);
}