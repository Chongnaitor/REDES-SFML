#include<Graphics.hpp>
#include<Window.hpp>
#include<SFML/Network.hpp>
#include"Barra.h"
#include"Pelota.h"
#include"SoundManager.h"
#include<iostream>
#include<string>
#include<Windows.h>
bool Player1Done=false;
bool Player2Done=false;
bool Server=false;

sf::Packet BarraOnline1; 
sf::Packet BarraOnline2; 
sf::Packet PelotaOnline;
sf::RectangleShape Barraaa;
sf::RectangleShape Barra2;
sf::CircleShape Pelot;


//Ram es puto a ver si lee
void GameLoop();
void GameLoop()
{
	Barra HolaM;
	Pelota HolaMM;
	sf::Keyboard lmao;
	
	
	sf::TcpSocket P1;
	sf::TcpSocket P2;
	sf::TcpSocket PelotS;
	std::cout << "Antes de iniciar el juego tienes que conectarte." << std::endl;
	std::cout << "P1 para jugador, P1 para jugador 2 y S para servidor" << std::endl;
	sf::IpAddress IP = sf::IpAddress::getLocalAddress();
	std::string Decision;
	std::cin >> Decision;
	std::cin.ignore();

	if (Decision == "S")
	{
		sf::TcpListener Listener;
		Listener.listen(45000);
		Listener.accept(P1);
		Listener.accept(P2);
		Listener.accept(PelotS);

	}
	else if (Decision == "P1")
	{
		P1.connect(IP, 45000);
		P2.connect(IP, 45000);
		PelotS.connect(IP, 45000);
		
	}
	
	sf::RenderWindow GameWindow(sf::VideoMode(1000, 600), "Atomic Ball");
	GameWindow.setVerticalSyncEnabled(60);
	sf::Vector2f PrevPosition1,PrevPosition2, P1Position,P2Position,PelotaPrev,PelotaLocation;
	P1.setBlocking(false);
	P2.setBlocking(false);
	PelotS.setBlocking(false);
	

	while (GameWindow.isOpen())
	{

		GameWindow.clear();
		PrevPosition1 = Barraaa.getPosition();
		PrevPosition2 = Barra2.getPosition();
		PelotaPrev = Pelot.getPosition();
		sf::Event Game;
		while (GameWindow.pollEvent(Game))
		{
			

			if (Game.type == Game.Closed)
			{
				GameWindow.close();
			}
			
			
			
			HolaM.PlayerMovement(Barraaa, Barra2, Game, P1);
				
			
		
		}

		
		HolaMM.MoverPelota(HolaM.Collider(Barraaa, Pelot), HolaM.Collider(Barra2, Pelot), Pelot);
		HolaMM.BounderiesColider(Pelot, GameWindow);
		sf::Packet packet;
		sf::Packet packet2;
		sf::Packet packet3;
		if (PrevPosition1 != Barraaa.getPosition())
		{
			packet << Barraaa.getPosition().x << Barraaa.getPosition().y;
			P1.send(packet);
		}
		P1.receive(packet);
		if (packet >> P1Position.x >> P1Position.y)
		{
			Barraaa.setPosition(P1Position);
		}

		if (PrevPosition2 != Barra2.getPosition())
		{

			packet2 << Barra2.getPosition().x << Barra2.getPosition().y;
			P2.send(packet2);

		}
		P2.receive(packet2);
		if (packet2 >> P2Position.x >> P2Position.y)
		{
			Barra2.setPosition(P2Position);


		}
		if (PelotaPrev != Pelot.getPosition())
		{
			packet3 << Pelot.getPosition().x << Pelot.getPosition().y;
			PelotS.send(packet3);
		}
		PelotS.receive(packet3);
		if (packet3 >> PelotaLocation.x >> PelotaLocation.y)
		{
			Pelot.setPosition(PelotaLocation);
		}
		GameWindow.draw(Barraaa);
		GameWindow.draw(Barra2);
		GameWindow.draw(Pelot);
		GameWindow.display();
		

		
		
		
	}




}
void Menu(sf::RenderWindow& GameWindow)
{
	
	
		sf::Event evento;
		sf::Keyboard teclado;
		sf::Texture fondo;
		fondo.loadFromFile("Fondo.png", sf::IntRect(0, 0, 1000, 600));
		sf::Sprite ff;
		ff.setTexture(fondo);

		while (GameWindow.isOpen())
		{
			GameWindow.pollEvent(evento);
			if (evento.type == evento.KeyPressed)
			{
				if (evento.key.code == teclado.Enter)
				{
					GameLoop();
				}

			}
			GameWindow.draw(ff);
			GameWindow.display();
		
	    }
}

int main()
{


	GameLoop();
	
	return 0;
}