#include "CollisionManager.h"

void CollisionManager::check_tiles(){
	//check collision for each entity between each tile for now
	//some time later i can optimize this
	//for no i need all entities and all tiles, check one against all and all against one
	std::vector<Tile*>::iterator begin_tile = Level::instance()->get_beign();
	std::vector<Tile*>::iterator end_tile = Level::instance()->get_end();
	std::vector<Entity*>::iterator begin_ent = EntityManager::instance()->get_beign();
	std::vector<Entity*>::iterator end_ent = EntityManager::instance()->get_end();
	
	//for every entity
	for(begin_ent; begin_ent != end_ent; begin_ent++){
		//for every tile
		for(begin_tile; begin_tile != end_tile; begin_tile++){
			if((*begin_tile)->get_sprite()->getGlobalBounds().intersects(
				(*begin_ent)->getRect()->getGlobalBounds())){
					std::cout<<" collided \n";
			}
		}
	}
}
void CollisionManager::collision_response(Tile* t, Entity* entity){
	//determine if your above, below, to the left or to the right of the fucking thing 	
	sf::Vector2f tile = t->get_position();
	sf::Vector2f ent = entity->getPosition();

	//gotta do something about them top right corners too right ???
	//im pretty sure the origin is top right corner
	//with that in mind
	//get centre
	tile.x = tile.x + (t->get_sprite()->getGlobalBounds().width/2);
	tile.y = tile.y + (t->get_sprite()->getGlobalBounds().height/2);
	ent.x = ent.x + (entity->getRect()->getGlobalBounds().width/2);
	ent.y = ent.y + (entity->getRect()->getGlobalBounds().height/2);


	//check vertical
	if(ent.y > tile.y){//below, since 0  0 is top kek
	}
	else{//below
	}
	//check horizontal
	if(ent.x > tile.x){//below, since 0  0 is top kek
	}
	else{//below
	}

}