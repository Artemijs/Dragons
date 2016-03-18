
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>
#include "Dragon.h"
#include "State.h"
#include "EntityManager.h"
#include "FlagPool.h"
void manageInput(sf::Event event, sf::Vector2i mousePos);
int main() {
	sf::Clock clock; // starts the clock
	sf::RenderWindow window(sf::VideoMode(512, 384), "Test Window");
	window.setFramerateLimit(30);

	Dragon* c = new Dragon(0);
	fptr state = action_idle;
	c->setState(state);
	EntityManager::instance()->addEntity(c);
	sf::Time deltaTime = clock.getElapsedTime();
	while (window.isOpen()) {
		deltaTime = clock.restart();
		sf::Event event;
		//
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			manageInput(event, sf::Mouse::getPosition(window));
		}
		FlagPool::instance()->update(deltaTime.asMilliseconds());
		EntityManager::instance()->update(deltaTime.asMilliseconds());
		//c->update(deltaTime.asMilliseconds());
		window.clear();
		EntityManager::instance()->draw(&window);
		window.display();
	}
	
	return 0;
}
void manageInput(sf::Event event, sf::Vector2i mousePos){
	if(event.type == sf::Event::MouseButtonPressed){
		Flag f;
		f.m_target = EntityManager::instance()->getEntity(0);
		f.text= "testing ";
		f.m_newState = action_move;
		FlagPool::instance()->addFlag(f);
	}
	if(event.type == sf::Event::MouseButtonReleased){
		Flag f;
		f.m_target = EntityManager::instance()->getEntity(0);
		f.text= "testing ";
		f.m_newState = action_idle;
		FlagPool::instance()->addFlag(f);
	}
	if(event.type == sf::Event::MouseMoved){
	}
	if (event.type == sf::Event::MouseWheelMoved){
	}
}