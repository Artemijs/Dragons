#ifndef MATH_H
#define MATH_H
#include "SFML\Graphics.hpp"
#include "Entity.h"
float math_get_lenght(sf::Vector2f vector);
sf::Vector2f math_normalize(sf::Vector2f vector);
sf::Vector2f math_get_direction(sf::Vector2f one, sf::Vector2f two);
float math_get_distance(sf::Vector2f one, sf::Vector2f two);
bool phys_basic_collision(sf::FloatRect one, sf::FloatRect two);
#endif