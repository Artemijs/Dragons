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
#include "Level.h"
#include "CollisionManager.h"
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
	Level::instance();
	CollisionManager* collision_manager = new CollisionManager();
	Dragon* c = new Dragon(0);
	c->setPosition(sf::Vector2f(50, SCREEN_HEIGHT/2));
	//Dragon* d = new Dragon(1);
	//d->setPosition(sf::Vector2f(600, SCREEN_HEIGHT/2));
	EntityManager::instance()->addEntity(c);
	//EntityManager::instance()->addEntity(d);
	sf::Time deltaTime = clock.getElapsedTime();
	Stars stars = Stars();
	while (window.isOpen()) {
		deltaTime = clock.restart();
		float deltaT = (deltaTime.asMilliseconds());
		deltaT/=1000;
		//std::cout<<(deltaT/1000);
	//	std::cout<<std::endl;
		MemoryChunk::instance()->reset();
		sf::Event event;
		//
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			manageInput(event, sf::Mouse::getPosition(window));
		}
		collision_manager->check_tiles();
		EntityManager::instance()->update(deltaT);
		//c->update(deltaTime.asMilliseconds());
		window.clear();
		EntityManager::instance()->draw(&window);
//		stars.move(c->getVelocity());
		Level::instance()->draw(&window);
		//stars.draw(&window);
		window.display();
	}
	delete c;
	delete EntityManager::instance();
	delete Level::instance();
	delete collision_manager;
	system("PAUSE");
	return 0;
}
void manageInput(sf::Event event, sf::Vector2i mousePos){
	EntityManager::instance()->getEntity(0)->setPosition(sf::Vector2f(mousePos.x, mousePos.y));
	if(event.type == sf::Event::MouseButtonPressed){
		

	}
	if(event.type == sf::Event::MouseButtonReleased){

	}
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::A){
			//EntityManager::instance()->getEntity(0)->rotate(-3);
			EntityManager::instance()->getEntity(0)->use_ability(1, 0);
		}
		if(event.key.code == sf::Keyboard::D){
			//EntityManager::instance()->getEntity(0)->rotate(3);
		}
	}
	if (event.type == sf::Event::MouseWheelMoved){
	}
}

/*
	list of shit that could use optimization
		collision detection
*/