#include "Barra.h"
#include <iostream>
Barra::Barra()
{
}



void Barra::PlayerMovement(sf::RectangleShape& PlayerBarra, sf::RectangleShape& PlayerBarra2, sf::Event& Whatever, sf::TcpSocket&P1)
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

	
	
	if (Whatever.type == sf::Event::KeyPressed)
	{
		if (Whatever.key.code == Controles.W)
		{

			if (Y != 0)
			{
				Y -= 100;
				//PlayerBarra.setPosition(X, Y);
			
			}



		}
		else if (Whatever.key.code == Controles.S)
		{
			if (Y != 400)
			{
				Y += 100;
				//PlayerBarra.setPosition(X, Y);
			}

		}
		else if (Whatever.key.code == Controles.Up)
		{

			if (Y2 != 0)
			{
				Y2 -= 100;
				//PlayerBarra2.setPosition(X2, Y2);
				
			}



		}
		else if (Whatever.key.code == Controles.Down)
		{
			if (Y2 != 400)
			{
				Y2 += 100;
				//PlayerBarra2.setPosition(X2, Y2);
				

			}

		}
		

	
	}
	//SendBarras(PlayerBarra, PlayerBarra2, P1);


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


