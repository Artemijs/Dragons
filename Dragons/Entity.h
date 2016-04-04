
#ifndef ftrp
typedef void (*fptr)(int id, float args[]);
#endif

#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp" 
#include <iostream>
#include "Ability.h"
#include "Stats.h"
//#include "BaseState.h"


class Entity{
protected:
	fptr m_state;
	int m_id;//index in the all entities array
	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	float* m_state_args;
	Stats* m_stats;
	std::vector<Ability*>* m_all_abilities;
	int m_selected_target;
public:
	Entity(int id);
	~Entity();
	fptr getState(){return m_state;}
	float* getArgs(){return m_state_args;}
	void setState(fptr newState, float* args);
	//void addVelocity(sf::Vector2f vel);
	void setDirection(sf::Vector2f newDir);
	sf::Vector2f getDirection(){return m_direction;}
	sf::Vector2f getPosition(){return m_position;}
	void setPosition(sf::Vector2f newPos);
	virtual void move(sf::Vector2f direction) =0;
	virtual void use_ability(int target, int aIndex) = 0;
	void take_damage(float dmg);
};

#endif