#include "Laser.h"

Laser::Laser(sf::Vector2f direction, sf::Vector2f startingPosition, sf::RenderWindow& window, SoundManager& soundManager)
	:movingDirection(direction), target(window), position(startingPosition)
{
	if (texture.loadFromFile("textures/laser.png"))
		sprite.setTexture(texture);

	sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2, static_cast<float>(texture.getSize().y) / 2);
	sprite.setPosition(position);

	float angle = std::atan2(movingDirection.y, movingDirection.x) * (180.f / 3.14f) + 90.f;
	sprite.setRotation(angle);

	soundManager.playLaserSound();
}

Laser::~Laser()
{

}

void Laser::logic(sf::Time delta)
{
	position += movingDirection * SPEED * delta.asSeconds();
	sprite.setPosition(position);

	if (timer.getElapsedTime().asSeconds() >= 1.5)
		destroyed = true;
	else
		destroyed = false;
}

void Laser::draw() const
{
	if(!destroyed)
		target.draw(sprite);
}

bool Laser::isDestroyed() const
{
	return destroyed;
}

sf::Vector2f Laser::getPosition()
{
	return position;
}

void Laser::setDestroyed()
{
	destroyed = true;
}