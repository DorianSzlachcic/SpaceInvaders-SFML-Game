#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow& window) :target(window)
{
	scene.push(std::make_unique<GameScene>(window));
}

SceneManager::~SceneManager()
{

}

void SceneManager::input(sf::Event& event)
{
    scene.top()->input(event);
}

void SceneManager::logic()
{
    scene.top()->logic();
}

void SceneManager::draw()
{
    scene.top()->draw();
}