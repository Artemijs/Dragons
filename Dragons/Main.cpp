#include "Macros.h"
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
class Star{
private:
	sf::CircleShape shape;
public:
	Star(){
		shape = sf::CircleShape((rand()%10));
		shape.setPosition(sf::Vector2f((rand()%SCREEN_WIDTH), (rand()%SCREEN_HEIGHT)));
	}
	sf::CircleShape getShape(){
		return shape;
	}
	void move(sf::Vector2f offset){
		sf::Vector2f pos = shape.getPosition()+offset;
		if((pos.x > SCREEN_WIDTH || pos.x < 0) ||(pos.y>SCREEN_HEIGHT || pos.y <0)){
			shape = sf::CircleShape((rand()%10));
			pos = (sf::Vector2f((rand()%SCREEN_WIDTH), (rand()%SCREEN_HEIGHT)));
		}


		shape.setPosition(pos);
	}
};
class Stars{
private:
	Star all_stars[10];
public:
	Stars(){
		for(int i =0; i < 10; i++){
			all_stars[i] = Star();
		}
	}
	void move(sf::Vector2f offset){
		for(int i =0; i < 10; i++){
			//all_stars[i].getShape().setPosition(all_stars[i].getShape().getPosition()+offset);
			all_stars[i].move(offset);
		}
	}
	void draw(sf::RenderWindow* window){
		for(int i =0; i < 10; i++){
			window->draw(all_stars[i].getShape());
		}
	}
};
int main() {
	sf::Clock clock; // starts the clock
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Window");
	window.setFramerateLimit(30);

	Dragon* c = new Dragon(0);
	fptr state = action_idle;
	c->setState(state, 0);
	EntityManager::instance()->addEntity(c);
	sf::Time deltaTime = clock.getElapsedTime();
	Stars stars = Stars();
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
		stars.move(c->getVelocity());
		stars.draw(&window);
		window.display();
	}
	delete c;
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
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::A){
			Flag f;
			f.m_target = EntityManager::instance()->getEntity(0);
			float* args = MemoryChunk::instance()->getArray();
			args[0] = 3;
			MemoryChunk::instance()->changeIndexBy(1);
			f.text= "rotate + ";
			f.args = args;
			f.m_newState = action_rotate;
			FlagPool::instance()->addFlag(f);
		}
		if(event.key.code == sf::Keyboard::D){
			Flag f;
			f.m_target = EntityManager::instance()->getEntity(0);
			float* args = MemoryChunk::instance()->getArray();
			args[0] = -3;
			MemoryChunk::instance()->changeIndexBy(1);
			f.text= "rotate - ";
			f.args = args;
			f.m_newState = action_rotate;
			FlagPool::instance()->addFlag(f);
		}
	}
	if (event.type == sf::Event::MouseWheelMoved){
	}
}
