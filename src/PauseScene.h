#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class PauseScene :public Scene
{
public:
    PauseScene() = delete;
    PauseScene(sf::RenderWindow& window);
    ~PauseScene() = default;

    void input(sf::Event& event) override;
    void logic() override;
    void draw() override;
};