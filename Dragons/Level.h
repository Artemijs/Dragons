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

class Level{
private:
	sf::Texture m_texture1;// ill later give this a proper name
	//and maybe put in an array
	std::vector<sf::Sprite*> m_all_tiles;
	Level();
	static Level* m_instance;
public:
	~Level();
	static Level* instance();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

};
#endif