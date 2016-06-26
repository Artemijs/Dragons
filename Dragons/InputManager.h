#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "SFML/Graphics.hpp" 
class InputManager{
private:
	bool m_keys[1024];
	static InputManager* m_instance;
	InputManager();
public:
	static InputManager* instance();
	void update(sf::Event event, sf::Vector2i mouse_pos);
	bool get_key(sf::Keyboard::Key key){return m_keys[key];}
};
#endif