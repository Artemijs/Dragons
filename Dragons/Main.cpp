
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>
#include "Entity.h"
#include "BaseState.h"
#include "EntityManager.h"
int main() {
	sf::Clock clock; // starts the clock
	sf::RenderWindow window(sf::VideoMode(512, 384), "Test Window");
	window.setFramerateLimit(30);
	Circle* c = new Circle(0);
	MovingState ms= MovingState();
	c->setState(ms);
	EntityManager::instance()->addEntity(c);
	sf::Time deltaTime = clock.getElapsedTime();
	while (window.isOpen()) {
		deltaTime = clock.restart();
		sf::Event event;
		//
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			//manageInput(event, sf::Mouse::getPosition(window));
		}
		c->update(deltaTime.asMilliseconds());
		window.clear();
		window.draw(c->getCircle());
		window.display();
	}
	return 0;
}
void manageInput(sf::Event event, sf::Vector2i mousePos){
	if(event.type == sf::Event::MouseButtonReleased){
	}
	if(event.type == sf::Event::MouseMoved){
	}
	if (event.type == sf::Event::MouseWheelMoved){
	}
}