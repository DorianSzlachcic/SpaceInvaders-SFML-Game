#include "SmallFastEnemy.h"

SmallFastEnemy::SmallFastEnemy(sf::RenderWindow& window, SoundManager& sounds)
	: Enemy::Enemy(window, sounds)
{
	if (texture.loadFromFile(filePath))
		sprite.setTexture(texture);

	setRandomPosition();
}

SmallFastEnemy::~SmallFastEnemy()
{
}

void SmallFastEnemy::logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime)
{
	handleCollisionsAndHealth(lasers, health);
	handleMoving(playerPosition, deltaTime, SPEED);
}
