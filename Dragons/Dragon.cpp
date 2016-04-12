#include "Dragon.h"
/*
to do:
hp below zero
mana below zero
hp/mana regen per second
movement and shit 
*/
Dragon::Dragon(int id):Entity(id), m_moveSpeed(5), m_angle(0){
	m_rect = sf::RectangleShape(sf::Vector2f(100, 30));
	m_rect.setOrigin(50, 15);
	m_rect.setPosition(m_position);
	m_cF = sf::CircleShape(5);
	m_cB = sf::CircleShape(5);
	m_cF.setPosition(m_position.x, m_position.y);
	m_cB.setPosition(m_position.x, m_position.y);
	m_cF.setOrigin(-48, 2);
	m_cB.setOrigin(52 , 2);
	m_cF.setFillColor(sf::Color::Red);
	m_cB.setFillColor(sf::Color::Blue);
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
	m_position += sf::Vector2f(0, 5);
	setPosition(m_position);
	(*m_all_abilities)[0]->update(deltaTime);
}

void Dragon::draw(sf::RenderWindow* window){
	window->draw(m_rect);
	window->draw(m_cF);
	window->draw(m_cB);
	(*m_all_abilities)[0]->draw(window);
}
void Dragon::rotate(float ang){
	m_rect.rotate(ang);
	m_cF.rotate(ang);
	m_cB.rotate(ang);
}
void Dragon::move(sf::Vector2f dir){
	//m_velocity= dir*m_moveSpeed;
}
void Dragon::use_ability(int target, int aIndex){
	
	Ability* ab = (*m_all_abilities)[aIndex];
	if(ab->get_state() != Ability_State::READY) return;
	m_stats->lose_mana(ab->get_mana_cost());
	ab->cast(target);
}
void Dragon::setPosition(sf::Vector2f newPos){
	m_position = newPos;
	m_rect.setPosition(newPos);
	m_cF.setPosition(newPos);
	m_cB.setPosition(newPos);
}