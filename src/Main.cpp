#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "Laser.h"
#include "BigSlowEnemy.h"
#include "NormalEnemy.h"
#include "SmallFastEnemy.h"
#include "SoundManager.h"
#include "Points.h"


const int WIDTH = 1000;
const int HEIGHT = 700;

template <class T> void removeDestroyedObjects(std::list<std::shared_ptr<T>>& list);
void generateEnemies(std::list<std::shared_ptr<Enemy>>& enemies, sf::RenderWindow& window, SoundManager& soundManager);

int main()
{
	sf::RenderWindow window{ sf::VideoMode{WIDTH,HEIGHT}, "Space Invaders", sf::Style::Close };
	sf::Image cursorImage;
	sf::Cursor cursor;
	if (cursorImage.loadFromFile("textures/cursor.png"))
		cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u{ cursorImage.getSize().x/2, cursorImage.getSize().y/2});
	window.setMouseCursor(cursor);

	sf::Texture backgroundTexture;
	sf::Sprite background;
	if (backgroundTexture.loadFromFile("textures/space.jpg"))
		background.setTexture(backgroundTexture);
	background.setScale(2, 2);
	background.setPosition(-50, -50);

	SoundManager soundManager;
	soundManager.playMusic();

	srand(unsigned(time(0)));
	std::list<std::shared_ptr<Laser>> lasers;
	std::unique_ptr<Player> player = std::make_unique<Player>( window, sf::Vector2f{WIDTH / 2,HEIGHT / 2}, lasers, soundManager );
	std::list<std::shared_ptr<Enemy>> enemies;
	Points points{ window };

	sf::Clock timer;
	while (window.isOpen())
	{
		sf::Event event;
		bool restart = false;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
				restart = true;

			player->input();
		}

		sf::Time deltaTime = timer.restart();
		player->logic(deltaTime);

		for (auto& e : enemies)
		{
			e->logic(player->getPosition(), lasers, deltaTime);

			if (e->isDestroyed())
				points.scoreUp();

			if (player->getGlobalBounds().contains(e->getPosition()))
			{
				restart = true;
			}
		}

		if (restart)
		{
			player = std::make_unique<Player>(window, sf::Vector2f{ WIDTH / 2,HEIGHT / 2 }, lasers, soundManager);
			enemies.clear();
			lasers.clear();
			points.reset();
		}

		removeDestroyedObjects(lasers);
		removeDestroyedObjects(enemies);
		generateEnemies(enemies, window, soundManager);

		window.clear(sf::Color::Black);
		window.draw(background);
		for (const auto& l : lasers)
			l->draw();
		for (const auto& e : enemies)
			e->draw();
		player->draw();
		points.draw();
		window.display();
	}

	return 0;
}

template <class T> 
void removeDestroyedObjects(std::list<std::shared_ptr<T>>& list)
{
	std::list<std::shared_ptr<T>> toRemove;
	for (auto& l : list)
	{
		if (l->isDestroyed())
			toRemove.push_back(l);
	}
	if (!toRemove.empty())
		for (auto& r : toRemove)
			list.remove(r);
}

void generateEnemies(std::list<std::shared_ptr<Enemy>>& enemies, sf::RenderWindow& window, SoundManager& soundManager)
{
	static sf::Clock enemyGenerationTimer;
	if (enemyGenerationTimer.getElapsedTime().asSeconds() >= static_cast<float>(rand()%10+15)/10)
	{
		std::shared_ptr<Enemy> ptr;
		switch (rand()%3+1)
		{
		case 1:
			ptr = std::make_shared<NormalEnemy>(window, soundManager);
			break;
		case 2:
			ptr = std::make_shared<BigSlowEnemy>(window, soundManager);
			break;
		case 3:
			ptr = std::make_shared<SmallFastEnemy>(window, soundManager);
			break;
		default:
			break;
		}
		enemies.push_back(ptr);
		enemyGenerationTimer.restart();
	}
}