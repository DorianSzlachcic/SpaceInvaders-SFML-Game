#pragma once
#include "Enemy.h"

class NormalEnemy :public Enemy
{
public:
	NormalEnemy(sf::RenderWindow& window, SoundManager& sounds);
	~NormalEnemy();

	void logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime) override;
};