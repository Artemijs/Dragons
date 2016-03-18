#include "Dragon.h"

Dragon::Dragon(int id):Entity(id){
	m_rect = sf::RectangleShape(sf::Vector2f(100, 30));
}
void Dragon::update(float deltaTime){
	/*	*m_position+=*m_velocity*incTime + 0.5*(*m_acceleration)*incTime*incTime;	
	if((*m_velocity).length() <= 100.0f)
		*m_velocity+=(*m_acceleration)*incTime;
		*/

	m_state(m_id, m_state_args);
	m_position+=m_velocity;
	m_rect.setPosition(m_position);
}
sf::RectangleShape Dragon::getRect(){
	return m_rect;
}
void Dragon::draw(sf::RenderWindow* window){
	window->draw(m_rect);
}
