#include "Funcs.h"

sf::Vector2f vectorNormalize(const sf::Vector2f& vec)
{
	float length = vectorLength(vec);
	if (length == 0)
		return vec;
	return sf::Vector2f{ vec/length };
}

float vectorLength(const sf::Vector2f& vec)
{
	return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}