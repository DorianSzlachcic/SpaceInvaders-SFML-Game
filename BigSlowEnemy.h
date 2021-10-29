#pragma once
#include "Enemy.h"
class BigSlowEnemy :public Enemy
{
public:
	BigSlowEnemy(sf::RenderWindow& window, SoundManager& sounds);
	~BigSlowEnemy();

	void logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime) override;

private:
	const float SPEED = 100.f;
	int health = 10;
	std::string filePath = "textures/enemy2.png";
};