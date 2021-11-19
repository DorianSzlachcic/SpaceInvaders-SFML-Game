#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "SoundManager.h"
#include "Funcs.h"
#include "Laser.h"

class Player
{
public:
	Player(sf::RenderWindow& window, sf::Vector2f startingPosition, std::list<std::unique_ptr<Laser>>& laserList, SoundManager& sounds);
	~Player();

	void input();
	void logic(sf::Time delta);
	void draw();

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

private:
	const float ACCELERATION = 2000.f;
	const float FRICTION = 500.f;
	const float MAX_SPEED = 500.f;

	std::list<std::unique_ptr<Laser>>& lasers;
	sf::RenderWindow& target;
	SoundManager& soundManager;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock shootTimer;

	int inputLeft = 0;
	int inputRight = 0;
	int inputUp = 0;
	int inputDown = 0;

	void shoot();
	void aiming();
	void moving(sf::Time delta);
};