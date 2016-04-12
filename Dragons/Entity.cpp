#include "Entity.h"
#include "Macros.h"
Entity::Entity(int id):m_id(id){
	m_direction = sf::Vector2f(0,0);
	m_position = sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_state_args = 0;
	m_stats = new Stats();
	
	m_all_abilities = new std::vector<Ability*>();
	m_all_abilities->push_back(new Ability_Ranged(id));
}
Entity::~Entity(){
	delete m_stats;
	//delete[] (*m_all_abilities);
	//delete m_state_args;
}
void Entity::setState(fptr newState, float* args){
	if(m_state == newState) return;

	m_state = newState;
	m_state_args = args;
	
}
void Entity::move_hard(sf::Vector2f dist){
	m_position+=dist;
}
void Entity::setDirection(sf::Vector2f newDir){
	m_direction = newDir;
}

void Entity::move(sf::Vector2f direction){
	m_direction = direction;
}
void Entity::take_damage(float dmg){
	m_stats->take_damage(dmg);
}
sf::RectangleShape* Entity::getRect(){
	return &m_rect;
}
void Entity::setPosition(sf::Vector2f newPos){
	m_position = newPos;
}