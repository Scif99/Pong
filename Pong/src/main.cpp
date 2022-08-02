#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include <iostream>
#include <string>

#include "ball.h"
#include "paddle.h"
#include "client.h"
#include "server.h"




int main()
{

    // Client or server ?
    std::string who;
    std::cout << "Do you want to be a server (s) or a client (c)? ";
    std::cin >> who;
    while (who != "s" && who != "c")
    {
        std::cout << "Error: Invalid input\nDo you want to be a server(s) or a client(c) ? ";
        std::cin >> who;
    }


    // Test the TCP protocol
    if (who == "s")
    {
        Server server;
        server.run();
    }
    else
    {
        sf::RenderWindow window(sf::VideoMode(800, 500), "Pong"); //Only client needs a window.
        Client client(window);
        client.run();
    }


    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');
    return 0;
}



