
#ifndef ftrp
typedef void (*fptr)(int id, float args[]);
#endif

#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp" 
#include <iostream>
//#include "BaseState.h"


class Entity{
protected:
	fptr m_state;
	int m_id;//index in the all entities array
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
public:
	Entity(int id);
	fptr getState(){return m_state;}
	void setState(fptr newState);
	void addVelocity(sf::Vector2f vel);
	void setVelocity(sf::Vector2f newVel);
	sf::Vector2f getVelocity(){return m_velocity;}
	sf::Vector2f getPosition(){return m_position;}
	void setPosition(sf::Vector2f newPos);
};
/*
class Circle : public Entity{
private:
	sf::CircleShape m_circle;
public:
	Circle(int id):Entity(id){
		m_circle = sf::CircleShape(10.0f);
	}
	void setPos(float x, float y){
		Entity::setPosition(x, y);
		m_circle.setPosition(x, y);
	}
	sf::CircleShape getCircle(){ return m_circle; }
	void update(float deltaTime){
		
		m_circle.setPosition(m_position);
		float args[2];
		args[0] = 1;
		args[1] = 0;
		m_state(m_id, args);
	}
};
*/
#endif