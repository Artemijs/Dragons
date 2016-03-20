#include "Dragon.h"

Dragon::Dragon(int id):Entity(id){
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
	/*	*m_position+=*m_velocity*incTime + 0.5*(*m_acceleration)*incTime*incTime;	
	if((*m_velocity).length() <= 100.0f)
		*m_velocity+=(*m_acceleration)*incTime;
		*/
	
	m_state(m_id, m_state_args);
	m_velocity+=sf::Vector2f(0, -5);
	//std::cout<<(m_cF.getPosition().x+48) <<"  "<<(m_cB.getPosition().x-52)<<" \n";
	//sf::Transform t = m_rect.getTransform();
	//m_cF.getTransform().combine(t);;
	//m_position+=m_velocity;
	//m_rect.setPosition(m_position);
}
sf::RectangleShape* Dragon::getRect(){
	return &m_rect;
}
void Dragon::draw(sf::RenderWindow* window){
	window->draw(m_rect);
	window->draw(m_cF);
	window->draw(m_cB);
}
void Dragon::rotate(float ang){
	m_rect.rotate(ang);
	m_cF.rotate(ang);
	m_cB.rotate(ang);
}