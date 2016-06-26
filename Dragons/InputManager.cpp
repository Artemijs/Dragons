#include "InputManager.h"
InputManager* InputManager::m_instance=0;
InputManager::InputManager(){
	for(int i =0; i < 1024; i++){
		m_keys[i] = false;
	}
}
InputManager* InputManager::instance(){
	if(m_instance == 0)
		m_instance = new InputManager();
	return m_instance;
}
void InputManager::update(sf::Event event, sf::Vector2i mouse_pos){
	if(event.type == sf::Event::KeyPressed){
		m_keys[event.key.code] = true;
	}
	if(event.type == sf::Event::KeyReleased){
		m_keys[event.key.code] = false;
	}
}
