#pragma once
#include "Enemy.h"

class SmallFastEnemy :public Enemy
{
public:
	SmallFastEnemy(sf::RenderWindow& window, SoundManager& sounds);
	~SmallFastEnemy();

	void logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime) override;
};