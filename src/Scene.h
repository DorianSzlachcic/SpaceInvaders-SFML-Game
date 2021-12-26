#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void input(sf::Event& event) = 0;
    virtual void logic() = 0;
    virtual void draw() = 0;
};