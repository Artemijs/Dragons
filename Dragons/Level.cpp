#include "Level.h"
#include "Macros.h"
#include <iostream>
Level* Level::m_instance = 0;
Level* Level::instance(){
	if(m_instance == 0)
		m_instance = new Level();
	return m_instance;
}

Level::Level(){
	m_all_tiles = std::vector<sf::Sprite*>();
	//for now just create them as even plane
	if (!m_texture1.loadFromFile("square.png", sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT)))
	{
		std::cout<<"failed loading tile texture \n";
	}
	for(int i =0; i < MAX_TILES_HORIZONTAL; ++i){
		sf::Vector2f pos = sf::Vector2f(0+i*TILE_WIDTH, SCREEN_HEIGHT*0.7);
		sf::Sprite* s = new sf::Sprite(m_texture1);
		s->setPosition(pos);
		m_all_tiles.push_back(s);

	}
}

Level::~Level(){
	//delete m_all_tiles;
	//delete m_instance;
}
void Level::update(float deltaTime){
	
}
void Level::draw(sf::RenderWindow* window){
	for(int i =0; i < m_all_tiles.size(); i++){
		window->draw((*m_all_tiles[i]));
	}
}