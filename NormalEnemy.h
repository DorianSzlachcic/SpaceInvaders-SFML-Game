#pragma once
#include "Enemy.h"

class NormalEnemy :public Enemy
{
public:
	NormalEnemy(sf::RenderWindow& window, SoundManager& sounds);
	~NormalEnemy();

	void logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime) override;

private:
	const float SPEED = 200.f;
	int health = 5;
	std::string filePath = "textures/enemy1.png";
};