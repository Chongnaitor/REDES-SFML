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
	
	sf::Text Score1;
	sf::Text Score2;
	sf::Font font;
	font.loadFromFile("Minecraft.ttf");
	Score1.setFont(font);
	Score2.setFont(font);
	Score1.setStyle(sf::Text::Bold);
	Score2.setStyle(sf::Text::Bold);
	Score1.setCharacterSize(40);
	Score2.setCharacterSize(40);
	Score1.setPosition(55, 55);
	Score2.setPosition(875, 55);
	Score1.setFillColor(sf::Color::White);
	Score2.setFillColor(sf::Color::White);
	sf::TcpSocket P1;
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

	}
	else if (Decision == "P1")
	{
		P1.connect(IP, 45000);
	}
	
	sf::RenderWindow GameWindow(sf::VideoMode(1000, 600), "Atomic Ball");
	GameWindow.setVerticalSyncEnabled(60);
	sf::Vector2f PrevPosition, P2Position;
	P1.setBlocking(false);
	bool Update = false;
	

	while (GameWindow.isOpen())
	{

		GameWindow.clear();
		PrevPosition = Barraaa.getPosition();
		sf::Event Game;
		while (GameWindow.pollEvent(Game))
		{
			

			if (Game.type == Game.Closed)
			{
				GameWindow.close();
			}
			
			
				HolaM.PlayerMovement(Barraaa, Barra2, Game, P1);
				
			
		
		}
		
		sf::Packet packet;
		if (PrevPosition != Barraaa.getPosition())
		{
			packet << Barraaa.getPosition().x << Barraaa.getPosition().y;
			P1.send(packet);
		}
		P1.receive(packet);
		if (packet >> P2Position.x >> P2Position.y)
		{
			Barra2.setPosition(P2Position);
		}
		if (PrevPosition != Barra2.getPosition())
		{
			packet << Barra2.getPosition().x << Barra2.getPosition().y;
			P1.send(packet);
		}
		P1.receive(packet);
		if (packet >> P2Position.x >> P2Position.y)
		{
			Barraaa.setPosition(P2Position);
		}
		GameWindow.draw(Barraaa);
		GameWindow.draw(Barra2);
		GameWindow.draw(Pelot);
		GameWindow.display();
		

		//HolaMM.MoverPelota(HolaM.Collider(Barraaa, Pelot), HolaM.Collider(Barra2, Pelot), Pelot);
		//HolaMM.BounderiesColider(Pelot, GameWindow);
		
		
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