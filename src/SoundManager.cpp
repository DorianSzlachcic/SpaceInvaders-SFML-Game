#include "SoundManager.h"

SoundManager::SoundManager()
{
	if (enemyBuffer.loadFromFile("sounds/enemyDeath.wav"))
		enemyDeathSound.setBuffer(enemyBuffer);
	enemyDeathSound.setVolume(25.f);

	if (laserBuffer.loadFromFile("sounds/laser.wav"))
		laserSound.setBuffer(laserBuffer);
	laserSound.setVolume(25.f);

	if (gameOverBuffer.loadFromFile("sounds/gameOver.wav"))
		gameOverSound.setBuffer(gameOverBuffer);
	gameOverSound.setVolume(100.f);

	gameMusic.openFromFile("sounds/gameMusic.wav");
	gameMusic.setLoop(true);
	gameMusic.setVolume(40.f);
	gameMusic.play();
}

SoundManager::~SoundManager()
{
}

void SoundManager::playGameOverSound()
{
	gameOverSound.play();
}

void SoundManager::playEnemyDeathSound()
{
	enemyDeathSound.play();
}

void SoundManager::playLaserSound()
{
	laserSound.play();
}

void SoundManager::playMusic()
{
	gameMusic.play();
}
