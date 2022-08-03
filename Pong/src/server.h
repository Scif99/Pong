#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <thread>
#include <array>

#include "common.h"
#include "ball.h"
#include "paddle.h"

constexpr unsigned short PORT{ 50001 };
constexpr unsigned short MAX_CLIENTS{ 1 };
class Server
{
public:
	Server()
	: m_ball_{ WIN_WIDTH/2, WIN_HEIGHT/2 },
		m_leftpaddle_{ 20.f, 0.f, Paddle::Side::LEFT },
		m_rightpaddle_{ WIN_WIDTH - 20.f, 0.f, Paddle::Side::RIGHT }{}
	~Server() {};

	void run();
	
	std::pair<int, int> ReceiveInput();
	void UpdateState(std::pair<int,int> input);
	void sendState();

private:
	std::array<sf::TcpSocket,2> m_clients_; //m_clients[0] will be the left player, m_clients[1] will be the right player
	Ball m_ball_;
	Paddle m_leftpaddle_;
	Paddle m_rightpaddle_;
	bool m_connected_;
};






