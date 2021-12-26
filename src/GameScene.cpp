#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow& window): target(window)
{
    if (cursorImage.loadFromFile("textures/cursor.png"))
		cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u{ cursorImage.getSize().x/2, cursorImage.getSize().y/2});
	window.setMouseCursor(cursor);

	
	if (backgroundTexture.loadFromFile("textures/space.jpg"))
		background.setTexture(backgroundTexture);
	background.setScale(2, 2);

	soundManager.playMusic();

	srand(unsigned(time(0)));
	
    player = std::make_unique<Player>( target, sf::Vector2f{static_cast<float>(target.getSize().x)/2,static_cast<float>(target.getSize().y)/2}, lasers, soundManager );
    points = std::make_unique<Points>(target);
}

void GameScene::input(sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
		restart = true;
}

void GameScene::logic()
{
    static sf::Clock timer;

    sf::Time deltaTime = timer.restart();
    player->logic(deltaTime);

    for (auto& e : enemies)
    {
        e->logic(player->getPosition(), lasers, deltaTime);

        if (e->isDestroyed())
            points->scoreUp();

        if (player->getGlobalBounds().contains(e->getPosition()))
        {
            restart = true;
        }
    }

    if (restart)
    {
        player = std::make_unique<Player>(target, sf::Vector2f{static_cast<float>(target.getSize().x)/2,static_cast<float>(target.getSize().y)/2}, lasers, soundManager);
        enemies.clear();
        lasers.clear();
        points->reset();
		restart = false;
    }

    removeDestroyedObjects(lasers);
    removeDestroyedObjects(enemies);
    generateEnemies(enemies, target, soundManager);
}

void GameScene::draw()
{
	target.draw(background);
	for (const auto& l : lasers)
		l->draw();
	for (const auto& e : enemies)
		e->draw();
	player->draw();
	points->draw();
}

template <class T> 
void GameScene::removeDestroyedObjects(std::list<std::unique_ptr<T>>& list)
{
	auto it = list.begin();
	auto itEnd = list.end();
	while (it != itEnd)
	{
		if ((*it)->isDestroyed())
			it = list.erase(it);
		else
			it++;
	}
}

void GameScene::generateEnemies(std::list<std::unique_ptr<Enemy>>& enemies, sf::RenderWindow& window, SoundManager& soundManager)
{
	static sf::Clock enemyGenerationTimer;
	if (enemyGenerationTimer.getElapsedTime().asSeconds() >= static_cast<float>(rand()%10+12)/10)
	{
		switch (rand()%3+1)
		{
		case 1:
			enemies.push_back(std::make_unique<NormalEnemy>(window, soundManager));
			break;
		case 2:
			enemies.push_back(std::make_unique<BigSlowEnemy>(window, soundManager));
			break;
		case 3:
			enemies.push_back(std::make_unique<SmallFastEnemy>(window, soundManager));
			break;
		default:
			break;
		}
		enemyGenerationTimer.restart();
	}
}