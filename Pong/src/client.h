#pragma once
#include <SFML/Network.hpp>

#include "common.h"
#include "ball.h"
#include "paddle.h"


class Client
{
public:
	Client()
		: m_ball_{ WIN_WIDTH / 2, WIN_HEIGHT / 2 },
		m_leftpaddle_{ 40.f, 0.f, Paddle::Side::LEFT },
		m_rightpaddle_{ WIN_HEIGHT - 20.f, 0.f, Paddle::Side::RIGHT}{}
	~Client() {};


	void run();
	void receiveState();
	void draw();
	void sendInput();
	void handleEvents();

private:
	sf::RenderWindow m_window_;
	sf::TcpSocket m_socket_;
	std::string m_name_;
	Ball m_ball_;
	Paddle m_leftpaddle_;
	Paddle m_rightpaddle_;
	bool m_connected_{false};
};

