#include "Points.h"

Points::Points(sf::RenderWindow& window): target(window)
{
	pointsCounter = 0;

	if (font.loadFromFile("textures/Font.ttf"))
	{
		score.setFont(font);
		lastScore.setFont(font);
	}

	score.setPosition(10, 10);

	lastScore.setString("Last score: \n0");
	lastScore.setPosition(target.getSize().x - lastScore.getGlobalBounds().width - 10, 10);
}

Points::~Points()
{
}

void Points::scoreUp()
{
	pointsCounter++;
}

void Points::reset()
{
	lastScore.setString("Last score: \n" + std::to_string(pointsCounter));
	pointsCounter = 0;
}

void Points::draw()
{
	score.setString("Score: \n" + std::to_string(pointsCounter));
	target.draw(score);
	target.draw(lastScore);
}
