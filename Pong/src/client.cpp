
#include "client.h"
#include <iostream>


constexpr unsigned short port{ 50001 };
void Client::run()
{
	// Ask for the server address
	sf::IpAddress server;
	std::cout << "Type the address of the server to connect to: ";
	std::cin >> server;

	//Store username
	std::cout << "Please enter a username: ";
	std::string name;
	std::cin >> name;
	m_name_ = name;

	// Connect to server
	std::cout << "connecting...\n";
	if (m_socket_.connect(server, port) != sf::Socket::Done)
	{
		std::cout << "Error: couldn't connect to server\n";
	}
	std::cout << "connected!\n";
	std::cout << "Waiting...\n";

	//The server will send a packet to notify the client that the game is ready to begin
	sf::Packet ready;
	if (m_socket_.receive(ready) != sf::Socket::Done)
	{
		std::cout << "Error\n";
	}

	m_connected_ = true;
	m_window_.create(sf::VideoMode(800, 500), "Pong"); //Only create window once the game is ready to start

	while (m_connected_)
	{
		draw();
		sendInput();
		receiveState(); //receive
		handleEvents();
	}

}

void Client::sendInput()
{
	int dir{ 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		dir = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dir = 1;
	}
	//Send packet to server
	sf::Packet packet;
	packet << dir;
	m_socket_.send(packet);
}

//Recieves state from server, and updates.
void Client::receiveState()
{
	sf::Packet state;
	if (m_socket_.receive(state) == sf::Socket::Disconnected)
	{
		std::cout << "Error: Server has ended\n";
		m_socket_.disconnect();
		return;
	}
	float bx, by,lpx,lpy,rpx,rpy;
	state >> bx >> by>>lpx>>lpy>>rpx>>rpy;
	m_ball_.setPosition(bx, by);
	m_leftpaddle_.setPosition(lpx, lpy);
	m_rightpaddle_.setPosition(rpx, rpy);

}


void Client::handleEvents()
{
	sf::Event event;
	while (m_window_.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			m_window_.close();
			m_socket_.disconnect();
		}
	}
}

void Client::draw()
{
	m_window_.clear();

	m_ball_.draw(m_window_);
	m_leftpaddle_.draw(m_window_);
	m_rightpaddle_.draw(m_window_);
	//m_name_.draw(m_window_);
	m_window_.display();
}