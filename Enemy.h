#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "Funcs.h"
#include "Laser.h"
#include "SoundManager.h"

class Enemy
{
public:
	Enemy(sf::RenderWindow& window, SoundManager& sounds);
	~Enemy();

	virtual void logic(sf::Vector2f playerPosition, std::list<std::shared_ptr<Laser>>& lasers, sf::Time deltaTime) = 0;
	virtual void draw() const;

	bool isDestroyed();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

protected:
	SoundManager& soundManager;
	bool destroyed = false;
	sf::RenderWindow& target;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

	virtual void handleCollisionsAndHealth(std::list<std::shared_ptr<Laser>>& lasers, int& health);
	virtual void handleMoving(sf::Vector2f playerPosition, sf::Time deltaTime, const float SPEED);
	virtual void setRandomPosition();
};

