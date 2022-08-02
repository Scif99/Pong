#include "server.h"
#include <future>


void Server::run()
{

	//Listen for a connection
	sf::TcpListener listener;
	if (listener.listen(PORT) != sf::Socket::Done)
	{
		std::cout << "Error: couldn't listen on specified port\n";
	}

	//Accept first client

	if (listener.accept(m_client_) != sf::Socket::Done)
	{
		std::cout << "Opponent failed to connect\n";

	}
	std::cout << "client has connected from " <<m_client_.getRemoteAddress() << " \n";
	m_connected_ = true;
	std::cout << "Starting game\n";



	while (m_connected_)
	{
		int dir{ 0 };
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		ReceiveInput(dir);
		std::cout << dir << '\n';
		UpdateState(dir);
		sendState();
	}
}


void Server::ReceiveInput(int& dir)
{
	

	sf::Packet packet;
	int input;

	if (m_client_.receive(packet) == sf::Socket::Disconnected)
	{
		std::cout << "Client disconnected. Ending session\n";
		m_client_.disconnect();
		m_connected_ = false;
		return;
	}
	packet >> input;
	dir = input;
}

//Takes the directions specified by clients, and updates game logic.
void Server::UpdateState(int dir)
{
	if (dir == -1)
	{
		paddle_coords.y -= paddle_coords.y > 40.f ? 10.f :0.f;
	}
	else if (dir == 1)
	{
		paddle_coords.y += paddle_coords.y < 500.f - 40.f ? 10.f : 0.f;
	}

	ball_coords.x += ball_velocity.x;
	ball_coords.y += ball_velocity.y;
}


//Recieves state from server, and updates.
void Server::sendState()
{
	sf::Packet out;
	out << ball_coords.x << ball_coords.y<<paddle_coords.x<<paddle_coords.y;
	if (m_client_.send(out) != sf::Socket::Done)
	{
		std::cout << "error sending state\n";
	}

}