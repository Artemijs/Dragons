#ifndef MATH_H
#define MATH_H
#include "SFML\Graphics.hpp"
#include "Level.h"
float math_get_lenght(sf::Vector2f vector);
sf::Vector2f math_normalize(sf::Vector2f vector);
sf::Vector2f math_get_direction(sf::Vector2f one, sf::Vector2f two);
float math_get_distance(sf::Vector2f one, sf::Vector2f two);
int math_random_range(int max, int min);
TILE_NEIGHBORS math_get_TN_from_dir(sf::Vector2f dir);

#endif