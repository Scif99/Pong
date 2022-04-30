#pragma once
#include <SFML/Graphics.hpp>

class Ball : sf::Drawable
{
public:
	Ball(float radius)
		:radius_{ radius }, circle_{ sf::CircleShape(radius_) }, pos_{circle_.getPosition()}
	{}

	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(circle_, states); }; //The draw function is inherited from the sf::Drawable class



	void move(int i);

	sf::CircleShape circle_;
private:
	float radius_;
	int speed[2];
	sf::Vector2f pos_;


};


void Ball::move(int i)
{
	if (i == 0)
	{
		circle_.setPosition(pos_ + sf::Vector2f(1.f,0.f));
	}
}