#pragma once
#include"Graphics.hpp"
#include"Audio.hpp"
class Pelota

{
public:
	int ID = 1;
	float Horizontal = 460;
	float Vertical = 200;
	bool lmao = false;
	bool lmao2 = false;
	int RandomRebound();
	sf::RectangleShape TopFrame;
	sf::RectangleShape BottomFrame;
	void MoverPelota(bool Collision, bool SecondCollision, sf::CircleShape& Pelota);
	void MoverPelota2(bool Collision, bool SecondCollision, sf::CircleShape& Pelota);
	void BounderiesColider(sf::CircleShape& Pelota, sf::RenderWindow& Lmao);
	bool FuckIt = false;
	bool FuckIt2 = false;
	int Score1 = 0;
	int Score2 = 0;

};

