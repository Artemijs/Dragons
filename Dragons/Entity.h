#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp" 
#include "BaseState.h"
class Entity{
protected:
	BaseState m_state;
	sf::Vector2f m_position;
	int m_id;//index in the all entities array
public:
	Entity(int id):m_id(id){
		
	}
	BaseState getState(){return m_state;}
	void setState(BaseState newState){
		m_state = newState;
	}
	sf::Vector2f getPosition(){return m_position;}
	void setPosition(float x, float y){m_position = sf::Vector2f(x, y);}
	void update(float deltaTime);
	
};
class Circle : public Entity{
private:
	sf::CircleShape circle;
public:
	Circle(int id):Entity(id){
		circle = sf::CircleShape(10.0f);
	}
	void setPos(float x, float y){
		Entity::setPosition(x, y);
		circle.setPosition(x, y);
	}
	sf::CircleShape getCircle(){ return circle; }
	void update(float deltaTime){
		float args[2];
		args[0] = 1;
		args[1] = 0;
		m_state.action(m_id, args);
	}
};
#endif