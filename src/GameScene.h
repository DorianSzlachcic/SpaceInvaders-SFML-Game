#pragma once
#include "Scene.h"
#include <memory>
#include <list>

#include "Player.h"
#include "Laser.h"
#include "BigSlowEnemy.h"
#include "NormalEnemy.h"
#include "SmallFastEnemy.h"
#include "SoundManager.h"
#include "Points.h"

class GameScene :public Scene
{
public:
    GameScene() = delete;
    GameScene(sf::RenderWindow& window);
    ~GameScene() = default;

    void input(sf::Event& event) override;
    void logic() override;
    void draw() override;

private:
    sf::RenderWindow& target;
    sf::Image cursorImage;
	sf::Cursor cursor;
    sf::Texture backgroundTexture;
	sf::Sprite background;
   	SoundManager soundManager;
    std::list<std::unique_ptr<Laser>> lasers;
	std::unique_ptr<Player> player;
	std::list<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<Points> points;

    bool restart = false;

    template <class T> 
    void removeDestroyedObjects(std::list<std::unique_ptr<T>>& list);
    void generateEnemies(std::list<std::unique_ptr<Enemy>>& enemies, sf::RenderWindow& window, SoundManager& soundManager);
};