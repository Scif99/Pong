#include "client.h"
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr unsigned short port{ 50001 };

void Client::run()
{
	// Ask for the server address
	sf::IpAddress server;
	std::cout << "Type the address of the server to connect to: ";
	std::cin >> server;

	// Connect to server

	std::cout << "connecting...\n";
	if (m_socket_.connect(server, port) != sf::Socket::Done)
	{
		std::cout << "Error: couldn't connect to server\n";
	}
	std::cout << "connected!\n";
	m_connected_ = true;

	while (m_connected_)
	{
		sendInput();
		receiveState(); //receive
		handleEvents(r_window_);
		draw();
	}

}

void Client::sendInput()
{
	int dir{ 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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
	m_socket_.receive(state);
	float bx, by,px,py;
	state >> bx >> by>>px>>py;
	m_ball_.setPosition(bx, by);
	m_paddle_.setPosition(px, py);


}


void Client::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			window.close();
			m_socket_.disconnect();
		}
	}
}

void Client::draw()
{
	r_window_.clear();

	m_ball_.draw(r_window_);
	m_paddle_.draw(r_window_);
	r_window_.display();
}