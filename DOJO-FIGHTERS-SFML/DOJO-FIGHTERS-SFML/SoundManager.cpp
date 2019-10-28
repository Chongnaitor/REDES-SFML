#include "SoundManager.h"

void SoundFX(int& GameID)
{
	sf::Sound Lmao;
	sf::SoundBuffer Lmao2;
	std::string Transformmm = std::to_string(GameID);
	std::string FileName = Transformmm + ".wav";
	Lmao2.loadFromFile(FileName);
	Lmao.setBuffer(Lmao2);
	Lmao.play();
}