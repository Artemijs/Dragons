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
	if(m_stats->get_stat(Stat_Type::CURR_HP)<0){
		//death
		m_state= EntityState::DEAD;
	}
}
sf::RectangleShape* Entity::getRect(){
	return &m_rect;
}
void Entity::setPosition(sf::Vector2f newPos){
	m_position = newPos;
}
void Entity::respawn(sf::Vector2f pos){
	/*
		reset:
			position
			stats

	*/
	m_position = pos;
	update_visual();
	m_stats->reset();
	m_state = EntityState::ALIVE;
}