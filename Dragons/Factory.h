#ifndef FACTORY_H
#define FACTORY_H
#include "Dragon.h"
#include "Macros.h"
//enemy factory
//fc == Factory_Create, otherwise the names are too long
int fc_dragon();
int fc_human();
Dragon* fc_dragon_ptr();
Human* fc_human_ptr();
int fc_randPos_dragon(sf::Vector2f max, sf::Vector2f min = VECTOR_ZERO);
Dragon* fc_randPos_dragon_ptr(sf::Vector2f max, sf::Vector2f min = VECTOR_ZERO);
#endif