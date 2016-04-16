#include "Factory.h"
#include "Math.h"
#include "EntityManager.h"
int fc_dragon(){
	Dragon* d = new Dragon(0);
	return EntityManager::instance()->addEntity(d);
}
int fc_human(){
	Human* d = new Human(0);
	return EntityManager::instance()->addEntity(d);
}
Dragon* fc_dragon_ptr(){
	Dragon* d = new Dragon(0);
	EntityManager::instance()->addEntity(d);
	return d;
}
Human* fc_human_ptr(){
	Human* d = new Human(0);
	EntityManager::instance()->addEntity(d);
	return d;
}
Dragon* fc_randPos_dragon_ptr(sf::Vector2f max, sf::Vector2f min){
	Dragon* d = new Dragon(0);
	EntityManager::instance()->addEntity(d);
	d->setPosition(
		sf::Vector2f(
		math_random_range(max.x, min.x),
		math_random_range(max.y, min.y))
		);
	return d;
}
int fc_randPos_dragon(sf::Vector2f max, sf::Vector2f min){
	Dragon* d = new Dragon(0);
	int id = EntityManager::instance()->addEntity(d);
	d->setPosition(
		sf::Vector2f(
		math_random_range(max.x, min.x),
		math_random_range(max.y, min.y))
		);
	return id;
}