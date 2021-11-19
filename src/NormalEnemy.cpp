#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(sf::RenderWindow& window, SoundManager& sounds)
	: Enemy::Enemy(window, sounds)
{
	speed = 350.f;
	health = 5;
	filePath = "textures/enemy1.png";
	if (texture.loadFromFile(filePath))
		sprite.setTexture(texture);

	setRandomPosition();
}

NormalEnemy::~NormalEnemy()
{
}

void NormalEnemy::logic(sf::Vector2f playerPosition, std::list<std::unique_ptr<Laser>>& lasers, sf::Time deltaTime)
{
	handleCollisionsAndHealth(lasers);
	handleMoving(playerPosition, deltaTime);
}
