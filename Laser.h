#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Laser
{
	friend class Enemy;
public:
	Laser(sf::Vector2f direction, sf::Vector2f startingPosition, sf::RenderWindow& window, SoundManager& soundManager);
	~Laser();

	void logic(sf::Time delta);
	void draw() const;

	bool isDestroyed() const;
	sf::Vector2f getPosition();

protected:
	void setDestroyed();

private:
	const float SPEED = 1000.f;
	bool destroyed = false;
	sf::RenderWindow& target;
	sf::Vector2f movingDirection;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock timer;
};

