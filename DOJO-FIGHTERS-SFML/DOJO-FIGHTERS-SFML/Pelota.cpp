#include "Pelota.h"
#include "SoundManager.h"
#include <cstdlib>
#include<iostream>
int Pelota::RandomRebound()
{
	int Numero = std::rand() % 35;
	return Numero;
}// hace que la pelota se muev aleatoriamente
void Pelota::MoverPelota(bool Collision, bool SecondCollision, sf::CircleShape& Pelota)
{

	sf::Color ColorP(255, 255, 255);
	Pelota.setRadius(25);
	Pelota.setPosition(Horizontal, Vertical);
	Pelota.setFillColor(ColorP);
	
	if (lmao == false && lmao2 == false)
	{

		if (Collision == true)
		{
			lmao = true;
			

		}
		Pelota.setPosition(Horizontal -= 10, Vertical);
		
	}

	if (lmao == true)
	{
		if (SecondCollision == true)
		{
			lmao = false;
			
		}
		Pelota.setPosition(Horizontal += 10, Vertical);

		
	}

	
}
void Pelota::MoverPelota2(bool Collision, bool SecondCollision, sf::CircleShape& Pelota)
{
	sf::Color ColorP(255, 255, 255);
	Pelota.setRadius(25);
	Pelota.setPosition(Horizontal, Vertical);
	Pelota.setFillColor(ColorP);

	if (lmao == false && lmao2 == false)
	{

		if (SecondCollision == true)
		{
			lmao = true;

		}
		Pelota.setPosition(Horizontal += 10, Vertical);

	}

	if (lmao == true)
	{
		if (Collision == true)
		{
			lmao = false;
		}
		Pelota.setPosition(Horizontal -=10, Vertical );


	}
	


}
void Pelota::BounderiesColider(sf::CircleShape& Pelota, sf::RenderWindow& Lmao)
{

	sf::Color color(62, 255, 206);
	BottomFrame.setSize(sf::Vector2f(200000.f, 2.f));
	TopFrame.setSize(sf::Vector2f(200000.f, 2.f));
	TopFrame.setPosition(1.f, 1.f);
	BottomFrame.setPosition(1.f, 599.f);
	BottomFrame.setFillColor(color);
	TopFrame.setFillColor(color);
	Lmao.draw(BottomFrame);
	Lmao.draw(TopFrame);
	sf::FloatRect BarraCollider = TopFrame.getGlobalBounds();
	sf::FloatRect BarraCollider2 = BottomFrame.getGlobalBounds();

	if (FuckIt == false && FuckIt2 == false)
	{
		if (BarraCollider.intersects(Pelota.getGlobalBounds()))
		{
			
		

			FuckIt = true;

		}
		Pelota.setPosition(Horizontal, Vertical -=30);

	}
	if (FuckIt == true)
	{
		if (BarraCollider2.intersects(Pelota.getGlobalBounds()))
		{
			
			FuckIt = false;
		}
		Pelota.setPosition(Horizontal, Vertical +=30);

	}
	

}