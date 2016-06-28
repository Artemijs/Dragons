#include "Dragon.h"
#include "Level.h"
#include "Math.h"
#include "Macros.h"
/*
to do:
hp below zero
mana below zero
hp/mana regen per second
movement and shit 
*/
Dragon::Dragon(int id):Entity(id), m_angle(0){
	m_rect = sf::RectangleShape(sf::Vector2f(30, 30));
	m_rect.setOrigin(15, 15);
	m_rect.setPosition(m_position);
	m_rect.setFillColor(sf::Color::Red);
}
void Dragon::update(float deltaTime){
	
	/*int dir =1;
	float ang = m_rect.getRotation();
	if(ang>0 && ang< 180){
		dir = -1;
	}
	std::cout<<"flying ";
	std::cout<<ang;
	std::cout<<"\n";
	ang = ang* (3.14/180);
	float f = 0.1f * 9 * std::sin(ang);
	sf::Vector2f slopeDir = sf::Vector2f(std::cos(ang), std::sin(ang));
	m_velocity = -slopeDir*m_moveSpeed;
	m_velocity+=sf::Vector2f(0, -5);
	*/
	m_position += sf::Vector2f(0, 5) + m_direction*m_stats->get_stat(Stat_Type::MOVE_SPEED); //gravity, ill rework this
	setPosition(m_position);
	(*m_all_abilities)[0]->update(deltaTime);
}

void Dragon::draw(sf::RenderWindow* window){
	window->draw(m_rect);
	(*m_all_abilities)[0]->draw(window);
}
void Dragon::rotate(float ang){
	m_rect.rotate(ang);
}
void Dragon::move(sf::Vector2f dir){
	m_direction = dir;
}
void Dragon::use_ability(int target, int aIndex){
	Ability* ab = (*m_all_abilities)[aIndex];
	if(ab->get_state() != Ability_State::READY) return;
	m_stats->lose_mana(ab->get_mana_cost());
	ab->cast(target);
	m_state = EntityState::CASTING;
}
void Dragon::setPosition(sf::Vector2f newPos){
	Entity::setPosition(newPos);
	update_visual();
	
}
void Dragon::update_visual(){
	m_rect.setPosition(m_position);
}
Dragon::~Dragon(){
	//delete m_stats;
}
Human::Human(int id):Entity(id){
	m_rect = sf::RectangleShape(sf::Vector2f(TILE_WIDTH/2, TILE_HEIGHT/2));
}
Human::~Human(){
	//delete m_stats;
}
void Human::update(float deltaTime){
	for(int i =0; i < (*m_all_abilities).size();++i)
		(*m_all_abilities)[i]->update(deltaTime);
	update_visual();
}
void Human::update_visual(){
	m_rect.setPosition(m_position);
}
void Human::draw(sf::RenderWindow* window){
	window->draw(m_rect);
	(*m_all_abilities)[0]->draw(window);
}
void Human::use_ability(int target, int aIndex){
	if(m_state != EntityState::IDLE)return;
	Ability* ab = (*m_all_abilities)[aIndex];
	if(ab->get_state() != Ability_State::READY) return;
	m_stats->lose_mana(ab->get_mana_cost());
	std::cout<<"casting"<<"\n";
	ab->cast(target);
	m_state = EntityState::CASTING;
}
