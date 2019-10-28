#include "Barra.h"
#include <iostream>
Barra::Barra()
{
}
void Barra::PlayerMovement(sf::RectangleShape& PlayerBarra, sf::RectangleShape& PlayerBarra2, sf::Event& Whatever, sf::TcpSocket& P1, sf::TcpSocket& P2)
{
	sf::Keyboard Controles;
	sf::Color BarColor(255, 255, 255);
	PlayerBarra.setSize(sf::Vector2f(25.f, 200.f));
	PlayerBarra.setFillColor(BarColor);
	sf::Color BarColor2(50, 255, 255);
	PlayerBarra2.setSize(sf::Vector2f(25.f, 200.f));
	PlayerBarra2.setFillColor(BarColor2);
	PlayerBarra2.setPosition(X2, Y2);
	PlayerBarra.setPosition(X, Y);
	sf::Packet WS;
	sf::Packet Arrws;
	P1.setBlocking(false);
	P2.setBlocking(false);
	WS << PlayerBarra.getPosition().x << PlayerBarra.getPosition().y;
	Arrws << PlayerBarra2.getPosition().x << PlayerBarra2.getPosition().y;
	P2.send(Arrws);
	P1.send(WS);
	if (Whatever.type == sf::Event::KeyPressed)
	{
		if (Whatever.key.code == Controles.W)
		{

			if (Y != 0)
			{
				Y -= 100;
				PlayerBarra.setPosition(X, Y);
				WS << PlayerBarra.getPosition().x << PlayerBarra.getPosition().y;
				P1.send(WS);
			}



		}
		else if (Whatever.key.code == Controles.S)
		{
			if (Y != 400)
			{
				Y += 100;
				PlayerBarra.setPosition(X, Y);
				WS << PlayerBarra.getPosition().x << PlayerBarra.getPosition().y;
				P1.send(WS);
			}

		}
		else if (Whatever.key.code == Controles.Up)
		{

			if (Y2 != 0)
			{
				Y2 -= 100;
				PlayerBarra2.setPosition(X2, Y2);
				Arrws << PlayerBarra2.getPosition().x << PlayerBarra2.getPosition().y;
				P2.send(Arrws);
			}



		}
		else if (Whatever.key.code == Controles.Down)
		{
			if (Y2 != 400)
			{
				Y2 += 100;
				PlayerBarra2.setPosition(X2, Y2);
				Arrws << PlayerBarra2.getPosition().x << PlayerBarra2.getPosition().y;
				P2.send(Arrws);

			}

		}
		P2.receive(WS);
		if (WS >> x >> y)
		{
			PlayerBarra.setPosition(x, y);
			std::cout << "Simin" << std::endl;
		}
		P1.receive(Arrws);
		if (Arrws >> x2 >> y2)
		{

			PlayerBarra2.setPosition(x2, y2);
			std::cout << "Simin" << std::endl;
		}
	}
	

	WS.clear();
	Arrws.clear();

}
bool Barra::Collider(sf::RectangleShape& Barra, sf::CircleShape& Pelota)
{
	sf::FloatRect BarraCollider = Barra.getGlobalBounds();
	if (BarraCollider.intersects(Pelota.getGlobalBounds()))
	{



		return true;
	}
	else if (!BarraCollider.intersects(Pelota.getGlobalBounds()))
	{
		return false;
	}
}