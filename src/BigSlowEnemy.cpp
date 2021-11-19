#include "BigSlowEnemy.h"

BigSlowEnemy::BigSlowEnemy(sf::RenderWindow& window, SoundManager& sounds)
	: Enemy::Enemy(window, sounds)
{
	speed = 250.f;
	health = 10;
	filePath = "textures/enemy2.png";

	if (texture.loadFromFile(filePath))
		sprite.setTexture(texture);

	setRandomPosition();
}

BigSlowEnemy::~BigSlowEnemy()
{
}

void BigSlowEnemy::logic(sf::Vector2f playerPosition, std::list<std::unique_ptr<Laser>>& lasers, sf::Time deltaTime)
{
	handleCollisionsAndHealth(lasers);
	handleMoving(playerPosition, deltaTime);
}
