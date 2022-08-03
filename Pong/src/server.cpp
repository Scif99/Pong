#include "server.h"
#include <functional>


void Server::run()
{

	//Listen for a connection
	sf::TcpListener listener;
	if (listener.listen(PORT) != sf::Socket::Done)
	{
		std::cout << "Error: couldn't listen on specified port\n";
	}

	std::cout<<"Server created. Listening on port " << PORT << '\n';

	//Accept clients
	for (auto& clnt : m_clients_)
	{
		if (listener.accept(clnt) != sf::Socket::Done)
		{
			std::cout << "Opponent failed to connect\n";
		}
		std::cout << "Client has connected from " << clnt.getRemoteAddress() << " \n";
	}


	//Now send a packet to each client, to notify them that the game is about to start
	std::cout << "Lobby full, ready to start game"<< " \n";
	for (auto& clnt : m_clients_)
	{
		sf::Packet packet;
		bool ready{ true };
		packet << ready;
		if (clnt.send(packet) != sf::Socket::Done)
		{
			std::cout << "Error: coulnt start game\n";
			return;
		}
	}

	m_connected_ = true;
	std::cout << "Starting game\n";
	while (m_connected_)
	{
		std::pair dir{ 0,0 };
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); //60fps
		auto p = ReceiveInput();
		std::cout << p.first<< p.second <<'\n';
		UpdateState(p);
		sendState();
	}
}


std::pair<int, int> Server::ReceiveInput()
{
	sf::Packet packet;
	int input;
	std::pair dir{ 0,0 };

	if (m_clients_[0].receive(packet) == sf::Socket::Disconnected)
	{
		std::cout << "Client disconnected. Ending session\n";
		std::for_each(std::begin(m_clients_), std::end(m_clients_), std::mem_fn(&sf::TcpSocket::disconnect));
		m_connected_ = false;
		return {0,0};
	}
	packet >> input;
	dir.first = input;

	packet.clear();

	if (m_clients_[1].receive(packet) == sf::Socket::Disconnected)
	{
		std::cout << "Client disconnected. Ending session\n";
		std::for_each(std::begin(m_clients_), std::end(m_clients_), std::mem_fn(&sf::TcpSocket::disconnect));
		m_connected_ = false;
		return {0,0};
	}
	packet >> input;
	dir.second = input; //FOR NOW< JUST COPY WHAT THE LEFT PLAYER DID

	return dir;
}

//Takes the directions specified by clients, and updates game logic.
void Server::UpdateState(std::pair<int,int> input)
{
	//update left paddle
	float left_vel{ 0.f };
	if (input.first == -1)
	{
		left_vel = m_leftpaddle_.getPosition().y > m_leftpaddle_.Dim().y / 2 ? -10.f : 0.f;

	}
	else if (input.first == 1)
	{
		left_vel = m_leftpaddle_.getPosition().y < WIN_HEIGHT - m_leftpaddle_.Dim().y / 2 ? 10.f : 0.f;
	}

	//update right paddle
	float right_vel{ 0.f };
	if (input.second == -1)
	{
		right_vel = m_rightpaddle_.getPosition().y > m_rightpaddle_.Dim().y / 2 ? -10.f : 0.f;

	}
	else if (input.second == 1)
	{
		right_vel = m_rightpaddle_.getPosition().y < WIN_HEIGHT - m_rightpaddle_.Dim().y / 2 ? 10.f : 0.f;
	}

	//Vertical collisions
	if (m_ball_.getPosition().y - m_ball_.getRadius() < 0.f || m_ball_.getPosition().y + m_ball_.getRadius() > WIN_HEIGHT)
	{
		m_ball_.setVelocity(m_ball_.velocity().x, -m_ball_.velocity().y);
	}

	//Ball going out of side bounds
	if (m_ball_.getPosition().x - m_ball_.getRadius() < 0.f || m_ball_.getPosition().x + m_ball_.getRadius() > WIN_WIDTH)
	{
		m_ball_.Reset(rand()%2);
	}

	HandleCollisions(m_leftpaddle_, m_ball_);
	HandleCollisions(m_rightpaddle_, m_ball_);
	m_leftpaddle_.move(0.f,left_vel);
	m_rightpaddle_.move(0.f, right_vel);
	m_ball_.move(m_ball_.velocity());
}



//Recieves state from server, and updates.
void Server::sendState()
{
	sf::Packet out;
	out << m_ball_.getPosition().x << m_ball_.getPosition().y 
		<< m_leftpaddle_.getPosition().x << m_leftpaddle_.getPosition().y
		<< m_rightpaddle_.getPosition().x<< m_rightpaddle_.getPosition().y;

	//Send the packet containng game state to each client
	for (auto& clnt : m_clients_)
	{
		if (clnt.send(out) != sf::Socket::Done)
		{
			std::cout << "error sending state\n";
		}
	}
}

