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
					collision_response((*begin_tile), (*begin_ent));
			}
		}
	}
}
void CollisionManager::collision_response(Tile* t, Entity* entity){
	//determine if your above, below, to the left or to the right of the fucking thing 	
	sf::FloatRect tile = t->get_sprite()->getGlobalBounds();
	sf::FloatRect ent = entity->getRect()->getGlobalBounds();

	//gotta do something about them top right corners too right ???
	//im pretty sure the origin is top right corner
	//with that in mind
	//get centre
	sf::Vector2f t_centre = sf::Vector2f(
	tile.left + (t->get_sprite()->getGlobalBounds().width/2),
	tile.top + (t->get_sprite()->getGlobalBounds().height/2)	
		);
	sf::Vector2f e_centre = entity->getPosition();
	//ent.x = ent.x + (entity->getRect()->getGlobalBounds().width/2);
	//ent.y = ent.y + (entity->getRect()->getGlobalBounds().height/2);

	float y_dist=0;
	//check vertical
	if(e_centre.y > t_centre.y){//below, since 0  0 is top kek
		//gotta get the bot y of ent 
		//top y of tile 
		//distance between them
		y_dist = tile.top + tile.height - ent.top ;
		std::cout<<" below "<<y_dist<<" \n";
	}
	else{//above
		y_dist = ent.top + ent.height - tile.top ;
		std::cout<<" above "<<y_dist<<" \n";
	}
	//check horizontal
	float x_dist = 0;
	if(e_centre.x > t_centre.x){//to the right
		x_dist = tile.left + tile.width - ent.left;
		std::cout<<" right "<<x_dist<<" \n";
	}
	else{//left
		x_dist =ent.left + ent.width - tile.left;
		std::cout<<" left "<<x_dist<<" \n";
	}

}