#ifndef LEVEL_H
#define LEVEL_H
#include "SFML\Graphics.hpp"
/*
for the moment
just create a very long square that is white of color
that moves in the oppositte direction to you while you stay still
and collision with it

the level will be :
TILED, so that you can randomize all the shit
	tiles will need to have a preset type for collision detection
	for example:
		flat tiles that you walk on
		curvy tiles for slopes and shit and idk what else, ill think of something
*/
class Tile{
private:
	sf::Sprite* m_sprite;//later an animated sprite
public:
	Tile(){}
	~Tile();
	sf::Vector2f get_position(){return m_sprite->getPosition();}
	sf::Sprite* get_sprite(){return m_sprite;}
	void set_sprite(sf::Sprite* sprt){
		m_sprite = sprt;
	}
};
class Level{
private:
	std::vector<Tile*> m_all_tiles;
	Level();
	static Level* m_instance;
public:
	~Level();
	static Level* instance();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	std::vector<Tile*>::iterator get_beign();
	std::vector<Tile*>::iterator get_end();
};
#endif