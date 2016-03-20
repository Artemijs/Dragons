#include "Entity.h"
#include "Macros.h"
Entity::Entity(int id):m_id(id){
	m_velocity = sf::Vector2f(0,0);
	m_position = sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_state_args = 0;
}
Entity::~Entity(){

	//delete m_state_args;
}
void Entity::setState(fptr newState, float* args){
	if(m_state == newState) return;

	m_state = newState;
	m_state_args = args;
	
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