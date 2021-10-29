#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& window, SoundManager& sounds)
	:target(window), soundManager(sounds)
{
}

Enemy::~Enemy()
{

}

void Enemy::draw() const
{
	target.draw(sprite);
}

bool Enemy::isDestroyed()
{
	return destroyed;
}

sf::Vector2f Enemy::getPosition()
{
	return position;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Enemy::handleCollisionsAndHealth(std::list<std::shared_ptr<Laser>>& lasers, int& health)
{
	for (auto& l : lasers)
	{
		if (sprite.getGlobalBounds().contains(l->getPosition()))
		{
			l->setDestroyed();
			health--;
			if (health <= 0)
			{
				destroyed = true;
				soundManager.playEnemyDeathSound();
			}
		}
	}
}

void Enemy::handleMoving(sf::Vector2f playerPosition, sf::Time deltaTime, const float SPEED)
{
	sf::Vector2f vec = playerPosition - position;

	position += vectorNormalize(vec) * SPEED * deltaTime.asSeconds();
	sprite.setPosition(position);

	float angle = std::atan2(vec.y, vec.x) * (180.f / 3.14) - 90.f;
	sprite.setRotation(angle);
}

void Enemy::setRandomPosition()
{
	int screenSide = rand() % 4 + 1;

	switch (screenSide)
	{
	case 1:
		position = sf::Vector2f{ -40, float(rand() % target.getSize().y) };
		break;
	case 2:
		position = sf::Vector2f{ float(rand() % target.getSize().x), -40 };
		break;
	case 3:
		position = sf::Vector2f{ float(target.getSize().x + 40), float(rand() % target.getSize().y) };
		break;
	case 4:
		position = sf::Vector2f{ float(rand() % target.getSize().x), float(target.getSize().y + 40) };
		break;
	}

	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(position);
}
