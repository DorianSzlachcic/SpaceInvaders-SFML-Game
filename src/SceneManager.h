#pragma once
#include <unistd.h>
#include <stack>
#include <memory>
#include "GameScene.h"

class SceneManager
{
public:
    SceneManager() = delete;
    SceneManager(sf::RenderWindow& window);
    ~SceneManager();

    void input(sf::Event& event);
    void logic();
    void draw();

private:
	std::stack<std::unique_ptr<Scene>> scene;
    sf::RenderWindow& target;
};