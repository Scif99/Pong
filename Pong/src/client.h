#pragma once
#include <SFML/Network.hpp>
#include "ball.h"
#include "paddle.h"



class Client
{
public:
	Client(sf::RenderWindow& window)
		: r_window_{ window }, m_ball_{ window.getSize().x / 2, window.getSize().y / 2 },
		m_paddle_{ 40.f, 0.f, Paddle::Side::LEFT } {}
	~Client() {};


	void run();
	void receiveState();
	void draw();
	void sendInput();
	void handleEvents(sf::RenderWindow& window);

private:
	sf::TcpSocket m_socket_;
	Ball m_ball_;
	Paddle m_paddle_;
	sf::RenderWindow& r_window_;
	bool m_connected_{false};
};

