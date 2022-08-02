#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "client.h"

#include "paddle.h"

constexpr unsigned short PORT{ 50001 };
constexpr unsigned short MAX_CLIENTS{ 1 };



class Server
{
public:
	Server() {};
	~Server() {};

	void run();
	
	void ReceiveInput(int& dir);
	void UpdateState(int input);
	void sendState();
	void handleCollisions();

private:
	sf::TcpSocket m_client_;

	sf::Vector2f ball_velocity{ -5.f,-2.f };
	sf::Vector2f ball_coords{400.f,250.f};
	sf::Vector2f paddle_coords{ 40.f,0.f };

	bool m_connected_;
};






