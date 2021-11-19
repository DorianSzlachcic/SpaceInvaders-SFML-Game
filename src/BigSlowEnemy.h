#pragma once
#include "Enemy.h"
class BigSlowEnemy :public Enemy
{
public:
	BigSlowEnemy(sf::RenderWindow& window, SoundManager& sounds);
	~BigSlowEnemy();

	void logic(sf::Vector2f playerPosition, std::list<std::unique_ptr<Laser>>& lasers, sf::Time deltaTime) override;
};