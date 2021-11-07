#pragma once
#include <SFML/Audio.hpp>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void playGameOverSound();
	void playEnemyDeathSound();
	void playLaserSound();
	void playMusic();

private:
	sf::SoundBuffer laserBuffer;
	sf::Sound laserSound;
	sf::SoundBuffer enemyBuffer;
	sf::Sound enemyDeathSound;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;
	sf::Music gameMusic;

};

