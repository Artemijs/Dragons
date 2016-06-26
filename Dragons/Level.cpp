#include "Level.h"
#include "Macros.h"
#include <iostream>
#include "GraphicsManager.h"
#include "Dragon.h"
#include "EntityManager.h"
#include "Math.h"
Level* Level::m_instance = 0;
Level* Level::instance(){
	if(m_instance == 0)
		m_instance = new Level();
	return m_instance;
}

Level::Level(){
	m_all_tiles = std::vector<Tile*>();
	//for now just create them as even plane
	for(int i =0; i < MAX_TILES_HORIZONTAL; ++i){
		for(int j =0; j < MAX_TILES_VERTICAL; ++j){
			sf::Vector2f pos = sf::Vector2f(0+i*TILE_WIDTH, j*TILE_HEIGHT);
			sf::Sprite* s = new sf::Sprite(
				*GraphicsManager::instance()->
				get_texture(TextureID::TILE_TEXTURE));
			s->setPosition(pos);
			s->setScale(TILE_WIDTH/s->getGlobalBounds().width, TILE_HEIGHT/s->getGlobalBounds().height);
			s->setColor(sf::Color(255, 255, 255 ,55));
			std::cout<<s->getGlobalBounds().width<<"\n";
			Tile* t = new Tile(m_all_tiles.size());
			t->set_sprite(s);
			m_all_tiles.push_back(t);
		}
	}
	create_graph();
	/*for(int i =0; i <10; i++){
		sf::Vector2f v = sf::Vector2f(math_random_range(6000, 0), SCREEN_HEIGHT/2);
		m_all_spawn.push_back(new SpawnPoint(v));
	}*/
}

Level::~Level(){
	std::cout<<"deleting level \n";
	for (std::vector< Tile* >::iterator it = m_all_tiles.begin() ; it != m_all_tiles.end(); ++it)
   {
     delete (*it);
   } 
	m_all_tiles.clear();
	for (std::vector< SpawnPoint* >::iterator it = m_all_spawn.begin() ; it != m_all_spawn.end(); ++it)
   {
     delete (*it);
   } 
	m_all_spawn.clear();
}
void Level::update(float deltaTime){
	for(int i =0; i < m_all_spawn.size(); i++){
		m_all_spawn[i]->update(deltaTime);
	}
}
void Level::draw(sf::RenderWindow* window){
	for(int i =0; i < m_all_tiles.size(); i++){
		window->draw((*m_all_tiles[i]->get_sprite()));
	}
}
void Level::create_graph(){
	std::vector<Tile*>::iterator tile = m_all_tiles.begin(); 
	std::vector<Tile*>::iterator end = m_all_tiles.end();
	int i =0;
	for(;tile != end; tile++){
		//get neighbours```
		//set neighbours
		if(i != 0)
			(*tile)->set_neighbor(TILE_NEIGHBORS::UP, m_all_tiles[i-1]);
		if(i + MAX_TILES_HORIZONTAL < m_all_tiles.size())
			(*tile)->set_neighbor(TILE_NEIGHBORS::RIGHT, m_all_tiles[i + MAX_TILES_HORIZONTAL]);
		if(i + 1 < m_all_tiles.size()) 
			(*tile)->set_neighbor(TILE_NEIGHBORS::DOWN, m_all_tiles[i + 1]);
		if(i - MAX_TILES_HORIZONTAL >=0)
			(*tile)->set_neighbor(TILE_NEIGHBORS::LEFT, m_all_tiles[i - MAX_TILES_HORIZONTAL]);
		//move on
		i++;
	}
}

Tile* Level::get_origin(){
	return m_all_tiles[0];
}

Tile::Tile(int id): m_id(id){
	m_neighbours.push_back(0);
	m_neighbours.push_back(0);
	m_neighbours.push_back(0);
	m_neighbours.push_back(0);
}
Tile* Tile::get_neighbor(TILE_NEIGHBORS tile_n){
	return m_neighbours[tile_n];//fuck you then
}
void Tile::set_neighbor( TILE_NEIGHBORS tile_n, Tile* n){
	m_neighbours[tile_n] = n;
}
std::vector<Tile*>::iterator Level::get_beign(){
	return m_all_tiles.begin();
}
std::vector<Tile*>::iterator Level::get_end(){
	return m_all_tiles.end();
}

Tile::~Tile(){
	delete m_sprite;
}


SpawnPoint::SpawnPoint(): m_position(VECTOR_ZERO), m_respawn_time(5), m_current_res_time(0), m_entity(0){}
SpawnPoint::SpawnPoint(sf::Vector2f pos, Entity* ent): m_position(pos), m_respawn_time(5), m_current_res_time(0), m_entity(ent){}
SpawnPoint::SpawnPoint(sf::Vector2f pos): m_position(pos), m_respawn_time(5), m_current_res_time(0){
	m_entity = new Dragon(0);
	m_entity->respawn(m_position);
	EntityManager::instance()->addEnemy(m_entity);
	//add enemy adds an entity and then adds it to the enemy array
}
void SpawnPoint::update(float deltaTime){
	if(m_entity == 0) return;
	if(m_entity->getState() == EntityState::DEAD){
		m_current_res_time+=deltaTime;
		if(m_current_res_time>= m_respawn_time){
			m_current_res_time = 0;
			m_entity -> respawn(m_position);
		}
	}
	//and maybe respawn him when he is too far from spawn point... later 
}

sf::Vector2f Tile::get_centre(){
	return m_sprite->getPosition()
		+sf::Vector2f(
		m_sprite->getGlobalBounds().width/2,
		m_sprite->getGlobalBounds().height/2
		);
}