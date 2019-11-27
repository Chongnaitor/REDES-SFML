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
sf::TcpSocket P1; sf::TcpSocket P2; sf::TcpListener server; sf::TcpSocket Temp;
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
	sf::RenderWindow GameWindow(sf::VideoMode(1000, 600), "Atomic Ball");
	GameWindow.setVerticalSyncEnabled(60);

	while (GameWindow.isOpen())
	{

		GameWindow.clear();
		sf::Event Game;
		while (GameWindow.pollEvent(Game))
		{

			if (Game.type == Game.Closed)
			{
				GameWindow.close();
			}
			if (Game.type == sf::Event::KeyPressed)
			{
				if (Game.key.code == lmao.Enter)
				{
					GameLoop();
				}
			}
			HolaM.PlayerMovement(Barraaa, Barra2, Game,P1,P2);
			
		}

		GameWindow.draw(Barraaa);
		GameWindow.draw(Barra2);
		GameWindow.draw(Pelot);
		//HolaMM.MoverPelota(HolaM.Collider(Barraaa, Pelot), HolaM.Collider(Barra2, Pelot), Pelot);
		//HolaMM.BounderiesColider(Pelot, GameWindow);
		
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
void OnlineConectionServer(std::string Decision)
{
	
	while (true)
	{
		
	
		std::string Message;
	

		if (Decision == "S")
		{

			char buffer[1024];

			server.listen(45000);
			std::cout << sf::IpAddress::getLocalAddress() << std::endl;
			std::cout << sf::IpAddress::getPublicAddress() << std::endl;
			std::size_t received = 0;
			std::string message;
			if (Player1Done != true)
			{
				server.accept(P1);
				std::cout << "Jugador 1 conectado desde la direccion " << P1.getRemoteAddress() << std::endl;
				P1.receive(buffer, sizeof(buffer), received);
				std::cout << "P1 ha dicho " << buffer << std::endl;
				message = " conectado P1";
				P1.send(message.c_str(), message.size() + 1);
				received = 0;
			}
			if (Player2Done != true)
			{
				memset(buffer, NULL, sizeof(buffer));
				server.accept(P2);
				std::cout << "Jugador 2 conectado desde la direccion " << P2.getRemoteAddress() << std::endl;
				P2.receive(buffer, sizeof(buffer), received);
				std::cout << "P2 ha dicho " << buffer << std::endl;
				message = " conectado P2";
				P2.send(message.c_str(), message.size() + 1);
			}
			server.setBlocking(false);

			Server = true;
			
		}
		

	}
	
	
}
void OnlineConectionP1(std::string Decision)
{

	while (true)
	{


		std::string Message;


		if (Decision == "P1")
		{
			char buffer[1024];
			if (Player2Done == true)
			{
				std::cout << "Ese lugar esta ocupado" << std::endl;
				system("cls");


			}
			std::cout << "Decide a que puerto te vas a conectar" << std::endl;
			std::cin >> Decision;
			P2.connect(Decision, 45000);

			Message = " me he conectado.\n";
			P2.send(Message.c_str(), Message.size() + 1);

			std::size_t received = 0;
			P2.receive(buffer, sizeof(buffer), received);
			std::cout << "El servidor dice: " << buffer << std::endl;

			Player2Done = true;
			P2.setBlocking(false);
			BarraOnline2 << Player2Done;
			P2.send(BarraOnline2);
			



		}
		GameLoop();




	}


}
void OnlineConectionP2(std::string Decision)
{

	while (true)
	{


		std::string Message;
	    if (Decision == "P2")
		{
			char buffer[1024];
			if (Player1Done == true)
			{
				std::cout << "Ese lugar esta ocupado" << std::endl;
				system("cls");


			}
			std::cout << "Decide a que puerto te vas a conectar" << std::endl;
			std::cin >> Decision;
			P1.connect(Decision, 45000);

			Message = " me he conectado.\n";
			P1.send(Message.c_str(), Message.size() + 1);

			std::size_t received = 0;
			P1.receive(buffer, sizeof(buffer), received);
			std::cout << "El servidor dice: " << buffer << std::endl;
			Player1Done = true;

			P1.setBlocking(false);

			BarraOnline1 << Player1Done;
			P1.send(BarraOnline1);
			
		

		
		


		}
		
		GameLoop();




	}


}
int main()
{

	std::cout << "Antes de iniciar el juego tienes que conectarte." << std::endl;
	std::cout << "P1 para jugador, P2 para jugador 2 y S para servidor" << std::endl;

	std::string Decision;
	std::cin >> Decision;
	std::cin.ignore();
	sf::Thread Server(OnlineConectionServer,Decision);
	if (Decision == "S")
	{
		Server.launch();
	}
	else if (Decision == "P1")
	{
		OnlineConectionP1(Decision);
	}
	else if (Decision == "P2")
	{
		OnlineConectionP2(Decision);
	}

	
	
	return 0;
}