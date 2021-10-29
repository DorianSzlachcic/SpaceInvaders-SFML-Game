#pragma once
#include <SFML/Graphics.hpp>
class Points
{
public:
	Points(sf::RenderWindow& window);
	~Points();

	void reset();
	void scoreUp();
	void draw();

private:
	sf::Font font;
	sf::Text score;
	sf::Text lastScore;
	sf::RenderWindow& target;
	int pointsCounter;
};

