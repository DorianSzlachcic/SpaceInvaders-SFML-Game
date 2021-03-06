#include "Player.h"

Player::Player(sf::RenderWindow& window, sf::Vector2f startingPosition, std::list<std::unique_ptr<Laser>>& laserList, SoundManager& sounds)
	: position(startingPosition), target(window), lasers(laserList), soundManager(sounds)
{
	if (texture.loadFromFile("textures/playerShip.png"))
		sprite.setTexture(texture);

	sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2, static_cast<float>(texture.getSize().y) / 2);
	sprite.setPosition(position);
}

Player::~Player()
{
	soundManager.playGameOverSound();
}

void Player::input()
{
	inputLeft = (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ? 1 : 0;
	
	inputRight = (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ? 1 : 0;

	inputUp = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ? 1 : 0;

	inputDown = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ? 1 : 0;
}

void Player::logic(sf::Time delta)
{
	input();
	moving(delta);
	aiming();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		shoot();

	for (auto& l : lasers)
		l->logic(delta);
}

void Player::draw()
{
	target.draw(sprite);
}

sf::Vector2f Player::getPosition()
{
	return position;
}

sf::FloatRect Player::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}
 
void Player::shoot()
{ 
	if (shootTimer.getElapsedTime().asSeconds() >= 0.15)
	{
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(target));
		sf::Vector2f vec = mousePosition - sprite.getPosition();
		lasers.push_back(std::make_unique<Laser>(vectorNormalize(vec), sprite.getPosition(), target, soundManager));

		shootTimer.restart();
	}
}

void Player::aiming()
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(target));
	sf::Vector2f vec = mousePosition - sprite.getPosition();

	float angle = std::atan2(vec.y, vec.x) * (180.f / 3.14f) + 90.f;
	sprite.setRotation(angle);
}

void Player::moving(sf::Time delta)
{
	sf::Vector2f inputVector{ static_cast<float>(inputRight - inputLeft),static_cast<float>(inputDown - inputUp) };
	inputVector = vectorNormalize(inputVector);

	if(vectorLength(velocity)<=MAX_SPEED)
		velocity += inputVector * ACCELERATION * delta.asSeconds();

	velocity += vectorNormalize(velocity) * -FRICTION * delta.asSeconds();

	//Checking collisions wih walls in X axis
	if (position.x < texture.getSize().x / 2)
	{
		if (velocity.x > 0)
			position.x += velocity.x * delta.asSeconds();
	}
	else if (position.x > target.getSize().x - texture.getSize().x / 2)
	{
		if (velocity.x < 0)
			position.x += velocity.x * delta.asSeconds();
	}
	else
	{
		position.x += velocity.x * delta.asSeconds();
	}

	//Checking collisions wih walls in Y axis
	if (position.y < texture.getSize().y / 2)
	{
		if (velocity.y > 0)
			position.y += velocity.y * delta.asSeconds();
	}
	else if (position.y > target.getSize().y - texture.getSize().y / 2)
	{
		if (velocity.y < 0)
			position.y += velocity.y * delta.asSeconds();
	}
	else
	{
		position.y += velocity.y * delta.asSeconds();
	}

	sprite.setPosition(position);
}
