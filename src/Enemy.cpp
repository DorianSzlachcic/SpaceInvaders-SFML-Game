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

bool Enemy::isDestroyed() const
{
	return destroyed;
}

sf::Vector2f Enemy::getPosition() const
{
	return position;
}

sf::FloatRect Enemy::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Enemy::handleCollisionsAndHealth(std::list<std::unique_ptr<Laser>>& lasers)
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

void Enemy::handleMoving(sf::Vector2f playerPosition, sf::Time deltaTime)
{
	sf::Vector2f vec = playerPosition - position;

	position += vectorNormalize(vec) * speed * deltaTime.asSeconds();
	sprite.setPosition(position);

	float angle = std::atan2(vec.y, vec.x) * (180.f / 3.14f) - 90.f;
	sprite.setRotation(angle);
}

void Enemy::setRandomPosition()
{
	int screenSide = rand() % 4 + 1;

	switch (screenSide)
	{
	case 1:
		position = sf::Vector2f{ -40, static_cast<float>(rand() % target.getSize().y) };
		break;
	case 2:
		position = sf::Vector2f{ static_cast<float>(rand() % target.getSize().x), -40 };
		break;
	case 3:
		position = sf::Vector2f{ static_cast<float>(target.getSize().x + 40), static_cast<float>(rand() % target.getSize().y) };
		break;
	case 4:
		position = sf::Vector2f{ static_cast<float>(rand() % target.getSize().x), static_cast<float>(target.getSize().y + 40) };
		break;
	default:
		break;
	}

	sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2, static_cast<float>(texture.getSize().y) / 2);
	sprite.setPosition(position);
}
