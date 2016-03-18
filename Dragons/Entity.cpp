#include "Entity.h"
Entity::Entity(int id):m_id(id){
	m_velocity = sf::Vector2f(0,0);
	m_position = sf::Vector2f(50,50);
}
void Entity::setState(fptr newState){
	if(m_state != newState)
		m_state = newState;
}
void Entity::addVelocity(sf::Vector2f vel){
	m_velocity += vel;
}
void Entity::setVelocity(sf::Vector2f newVel){
	m_velocity = newVel;
}
void Entity::setPosition(sf::Vector2f newPos){
	m_position = newPos;
}