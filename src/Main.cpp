#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stack>

#include "SceneManager.h"


const int WIDTH = 1700;
const int HEIGHT = 960;

int main()
{
	sf::RenderWindow window{ sf::VideoMode{WIDTH,HEIGHT}, "Space Invaders", sf::Style::Close };
	SceneManager sceneManager{window};
	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
				
			sceneManager.input(event);
		}

		sceneManager.logic();

		window.clear(sf::Color::Black);
		sceneManager.draw();
		window.display();
	}

	return 0;
}
