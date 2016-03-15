
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>
int main() {
	
	sf::RenderWindow window(sf::VideoMode(512, 384), "Test Window");
	window.setFramerateLimit(30);
	
	
	while (window.isOpen()) {
		sf::Event event;
		//
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			//manageInput(event, sf::Mouse::getPosition(window));
		}
		window.clear();
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