#pragma once
#include"Graphics.hpp"
#include"Window.hpp"
#include "Network.hpp"
#include <iostream>
class Barra
{
public:
	Barra();
	float Y = 100;
	float X = 0;
	float Y2 = 100;
	float X2 = 970;
	float x = 0; float y = 0;
	float x2 = 0; float y2 = 0;
	void PlayerMovement(sf::RectangleShape& PlayerBarra, sf::RectangleShape& PlayerBarra2, sf::Event& Whatever,sf::TcpSocket&P1,sf::TcpSocket&P2);
	bool Collider(sf::RectangleShape& Barra, sf::CircleShape& Pelota);
	void SendBarras(sf::RectangleShape& PlayerBarra, sf::RectangleShape& PlayerBarra2,sf::TcpSocket& P1, sf::TcpSocket& P2);
};