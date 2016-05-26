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
		CollisionManager* collision_manager = new CollisionManager();

		//Dragon* c = fc_dragon_ptr();
		//c->setPosition(sf::Vector2f(50, SCREEN_HEIGHT/2));
		Human* h = fc_human_ptr();
		h->setPosition(Level::instance()->get_origin()->get_centre() - h->get_HeightWidth());//);
		m_player = PlayerContainer(h, NULL);
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
				manageInput(event, sf::Mouse::getPosition(window));
			}
			view.setCenter(m_player.HUMAN->getPosition());
			collision_manager->check_entities();
			EntityManager::instance()->update(deltaT);
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
		delete collision_manager;
		system("PAUSE");
	}
	return 0;
}
void manageInput(sf::Event event, sf::Vector2i mousePos){
	
	if(event.type == sf::Event::MouseButtonPressed){
		//EntityManager::instance()->getEntity(0)->setPosition(sf::Vector2f(mousePos.x, mousePos.y));
	}
	if(event.type == sf::Event::MouseButtonReleased){

	}
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Left){
			m_player.HUMAN->move(sf::Vector2f(-1, 0));
		}
		if(event.key.code == sf::Keyboard::Right){
			m_player.HUMAN->move(sf::Vector2f(1, 0));
		}
		if(event.key.code == sf::Keyboard::Up){
			m_player.HUMAN->move(sf::Vector2f(0, -1));
		}
		if(event.key.code == sf::Keyboard::Down){
			m_player.HUMAN->move(sf::Vector2f(0, 1));
		}
		if(event.key.code == sf::Keyboard::Space){
			//jump
		}
	}
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
			m_player.HUMAN->move(sf::Vector2f(0, 0));
	}
	if (event.type == sf::Event::MouseWheelMoved){

	}
}

/*
	list of shit that could use optimization
		collision detection

*/
/*
	list of shit that would be a "quality of life" fix
		entity factory
*/