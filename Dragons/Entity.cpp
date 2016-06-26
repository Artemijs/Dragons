#include "Entity.h"
#include "Macros.h"
#include "Level.h"
Entity::Entity(int id):m_id(id){
	m_direction = sf::Vector2f(0,0);
	m_position = sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	m_stats = new Stats();
	m_all_abilities = new std::vector<Ability*>();
	m_all_abilities->push_back(new Ability_Step(id));
	m_all_abilities->push_back(new Ability_Blink(id));
	m_all_abilities->push_back(new Ability_Lance(id));
	m_current_tile = 0;
	m_state = EntityState::IDLE;
	m_nextState = EntityState::IDLE;
}
Entity::~Entity(){
	delete m_stats;
	//delete[] (*m_all_abilities);
	//delete m_state_args;
}
void Entity::move_hard(sf::Vector2f dist){
	m_position += dist;
}
void Entity::setDirection(sf::Vector2f newDir){
	m_direction = newDir;
}

void Entity::move(int newTile){
	if(m_state != EntityState::IDLE) return;
	/*Tile* neighbour = Level::instance()->
		get_tile(m_current_tile)->get_neighbor(TILE_NEIGHBORS(newTile));
	if(neighbour == 0)return;*/
	(*m_all_abilities)[0]->cast(newTile);
	set_state(EntityState::CASTING);
	/*if(set_state(EntityState::MOVING))return;//dont move if performing other action
	Tile* neighbor = Level::instance()->
		get_tile(m_current_tile)->get_neighbor(TILE_NEIGHBORS(newTile));
	if(neighbor == 0)
		return;
	m_current_tile = neighbor->get_id();*/
}
void Entity::take_damage(float dmg){
	m_stats->take_damage(dmg);
	if(m_stats->get_stat(Stat_Type::CURR_HP)<0){
		//death
		set_state(EntityState::DEAD);
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
	next_action();
}
bool Entity::set_state(EntityState newState){
	m_state = newState;
	return true;
}
void Entity::next_action(){
	m_state = m_nextState;
	m_nextState = EntityState::IDLE;
}
sf::Vector2f Entity::get_HeightWidth(){
	return sf::Vector2f(m_rect.getGlobalBounds().width/2,
		m_rect.getGlobalBounds().height/2);
}