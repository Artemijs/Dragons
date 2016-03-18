
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>
#include "Dragon.h"
#include "State.h"
#include "EntityManager.h"
#include "FlagPool.h"
#include "MemoryChunk.h"
void manageInput(sf::Event event, sf::Vector2i mousePos);
class Stars;
int main() {
	sf::Clock clock; // starts the clock
	sf::RenderWindow window(sf::VideoMode(512, 384), "Test Window");
	window.setFramerateLimit(30);

	Dragon* c = new Dragon(0);
	fptr state = action_idle;
	c->setState(state, 0);
	EntityManager::instance()->addEntity(c);
	sf::Time deltaTime = clock.getElapsedTime();
	while (window.isOpen()) {
		deltaTime = clock.restart();
		MemoryChunk::instance()->reset();
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
		float* args = MemoryChunk::instance()->getArray();
		args[0] = 0;
		args[1] = 1;
		MemoryChunk::instance()->changeIndexBy(2);
		f.text= "move ";
		f.args = args;
		f.m_newState = action_move;
		FlagPool::instance()->addFlag(f);
	}
	if(event.type == sf::Event::MouseButtonReleased){
		Flag f;
		f.m_target = EntityManager::instance()->getEntity(0);
		f.text= "idle ";
		f.m_newState = action_idle;
		FlagPool::instance()->addFlag(f);
	}
	if(event.type == sf::Event::MouseMoved){
	}
	if (event.type == sf::Event::MouseWheelMoved){
	}
}
class Star{
private:

public:
};
class Stars{
private:

public:
};