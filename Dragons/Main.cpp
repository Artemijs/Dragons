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
#include "Factory.h"
#include "PlayerContainer.h"
#include "AI.h"
#include "InputManager.h"
void manageInput();
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

void stm_main(){
	//std::cout<<"soon";
	AI ai;
	/*Item itm;
	itm.push_back(0);
	itm.push_back(0);
	itm.push_back(1);
	itm.push_back(0.5);
	itm.push_back(0);
	itm.push_back(1);
	itm.push_back(0);
	while(true){
		ai.feedForward(itm);
	}*/
}
PlayerContainer m_player;
int main() {
	std::string command = "game";
	if(!command.compare("")){
		std::cin>>command;
	}
	if( command == ("ai")){
		stm_main();
	}else if(command == ("game")){
	
	
		sf::Clock clock; // starts the clock
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Window");
		window.setFramerateLimit(30);
		sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		window.setView(view);
		Level::instance();
		

		//Dragon* c = fc_dragon_ptr();
		//c->setPosition(sf::Vector2f(50, SCREEN_HEIGHT/2));
		Human* h = fc_human_ptr();
		h->setPosition(Level::instance()->get_origin()->get_centre() - h->get_HeightWidth());//);
		h->set_tile(Level::instance()->get_origin()->get_id());
		m_player = PlayerContainer(h, NULL);

		h = fc_human_ptr();
		h->setPosition(Level::instance()->get_tile(15)->get_centre() - h->get_HeightWidth());//);
		h->set_tile(Level::instance()->get_tile(15)->get_id());
		//h = fc_human_ptr();
		//h->setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
		sf::Time deltaTime = clock.getElapsedTime();
		Stars stars = Stars();

		while (window.isOpen()) {
			deltaTime = clock.restart();
			float deltaT = (deltaTime.asMilliseconds());
			deltaT/=1000;

			//std::cout<<(deltaT/1000);
		//	std::cout<<std::endl;
			//MemoryChunk::instance()->reset();
			sf::Event event;
			//
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				InputManager::instance()->update(event, sf::Mouse::getPosition(window));
				
			}
			
			//view.setCenter(m_player.HUMAN->getPosition());
			//CollisionManager::instance()->check_entities();
			EntityManager::instance()->update(deltaT);
			manageInput();
			window.setView(view);
			window.clear();
			EntityManager::instance()->draw(&window);
	//		stars.move(c->getVelocity());
			Level::instance()->draw(&window);
			stars.draw(&window);
			window.display();
		}
		//delete c;
		delete EntityManager::instance();
		delete Level::instance();
		delete CollisionManager::instance();
		system("PAUSE");
	}
	return 0;
}
void manageInput(){
	AbilityIndex ability = AbilityIndex::NO_SPELL;
	if(InputManager::instance()->get_key(sf::Keyboard::Q))
		ability = AbilityIndex::SPELL2;
	if(InputManager::instance()->get_key(sf::Keyboard::W))
		ability = AbilityIndex::SPELL3;
	bool spell = (ability != AbilityIndex::NO_SPELL);
	TILE_NEIGHBORS dir = TILE_NEIGHBORS::NONE;

	if(InputManager::instance()->get_key(sf::Keyboard::Left)){
			//m_player.HUMAN->move(TILE_NEIGHBORS::LEFT);
		dir = TILE_NEIGHBORS::LEFT;
	}
	if(InputManager::instance()->get_key(sf::Keyboard::Right)){
		//m_player.HUMAN->move(TILE_NEIGHBORS::RIGHT);
		dir = TILE_NEIGHBORS::RIGHT;
	}
	if(InputManager::instance()->get_key(sf::Keyboard::Up)){
		//m_player.HUMAN->move(TILE_NEIGHBORS::UP);
		dir = TILE_NEIGHBORS::UP;
	}
	if(InputManager::instance()->get_key(sf::Keyboard::Down)){
		//m_player.HUMAN->move(TILE_NEIGHBORS::DOWN);
		dir = TILE_NEIGHBORS::DOWN;
	}
	if(dir != TILE_NEIGHBORS::NONE)
		if(!spell){
			m_player.HUMAN->move(dir);
		}
		else{
		
			m_player.HUMAN->use_ability(dir, ability);
		}
}
/*
	known minor bugs:
		abilities dont use mana afaik
		abilities casting at the same time, uses old tile id and jump to wrong location
		collision with 2 players
		dealing damage once and not while collided
		movement is still buggy
		out of health 
		out of mana
		

*/
/*
	list of shit that could use optimization
		collision detection

*/
/*
	list of shit that would be a "quality of life" fix
		entity factory
		change m_my_id to caster id to avoid confusion
*/
/*
	list of regrets:
		Entity inheritance is all messed up 
		I dont know how to do the movement, idk why but it confuses me profoundly

*/