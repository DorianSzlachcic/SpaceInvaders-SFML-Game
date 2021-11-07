#include "SmallFastEnemy.h"

SmallFastEnemy::SmallFastEnemy(sf::RenderWindow& window, SoundManager& sounds)
	: Enemy::Enemy(window, sounds)
{
	speed = 400.f;
	health = 2;
	filePath = "textures/enemy3.png";

	if (texture.loadFromFile(filePath))
		sprite.setTexture(texture);

	setRandomPosition();
}

SmallFastEnemy::~SmallFastEnemy()
{
}

void SmallFastEnemy::logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime)
{
	handleCollisionsAndHealth(lasers);
	handleMoving(playerPosition, deltaTime);
}
