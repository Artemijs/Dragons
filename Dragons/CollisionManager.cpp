#include "CollisionManager.h"
#include "Macros.h"
CollisionManager* CollisionManager::m_instance=0;
CollisionManager* CollisionManager::instance(){
	if(m_instance == 0)
		m_instance = new CollisionManager();
	return m_instance;
}
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
		for(std::vector<Tile*>::iterator b_tile = begin_tile; b_tile != end_tile; b_tile++){
			//std::cout<<(*begin_ent)<<" \n";
			if((*b_tile)->get_sprite()->getGlobalBounds().intersects(
				(*begin_ent)->getRect()->getGlobalBounds())){
					collision_response((*b_tile), (*begin_ent));
			}
		}
	}
}
void CollisionManager::check_entities(){
	//check collision for each entity with each other entity for now
	//some time later i can optimize this
	//at the given moment im strugling to come up with better names for these
	std::vector<Entity*>::iterator begin_ent = EntityManager::instance()->get_beign();
	std::vector<Entity*>::iterator end_ent = EntityManager::instance()->get_end();
	std::vector<Entity*>::iterator begin_ent1 = EntityManager::instance()->get_beign();
	std::vector<Entity*>::iterator end_ent1 = EntityManager::instance()->get_end();
	//for every entity
	for(begin_ent; begin_ent != end_ent; begin_ent++){
		//for every tile
		
		for(std::vector<Entity*>::iterator b_ent1 = begin_ent1; b_ent1 != end_ent1; b_ent1++){
			//std::cout<<(*begin_ent)<<" \n";
			if(b_ent1 != begin_ent)
				if((*b_ent1)->getRect()->getGlobalBounds().intersects(
					(*begin_ent)->getRect()->getGlobalBounds())){
						collision_response((*b_ent1), (*begin_ent));
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
	int x_dir =1;//this is needed to etermine in which direction to push, left right or up/down
	int y_dir =1;
	//check vertical
	if(e_centre.y > t_centre.y){//below, since 0  0 is top kek
		//gotta get the bot y of ent 
		//top y of tile 
		//distance between them
		y_dist = tile.top + tile.height - ent.top ;
		y_dir = 1;
		//std::cout<<" below "<<y_dist<<" \n";

	}
	else{//above
		y_dist = ent.top + ent.height - tile.top - GRAVITY;
		y_dir = -1;
		//std::cout<<" above "<<y_dist<<" \n";
	}
	//check horizontal
	float x_dist = 0;
	if(e_centre.x > t_centre.x){//to the right
		x_dir = 1;
		x_dist = tile.left + tile.width - ent.left;
		//std::cout<<" right "<<x_dist<<" \n";
	}
	else{//left
		x_dir = -1;
		x_dist =ent.left + ent.width - tile.left;
		//std::cout<<" left "<<x_dist<<" \n";
	}

	if(x_dist < y_dist){
		entity->move_hard(sf::Vector2f(x_dist*x_dir, 0));
	}
	else if(y_dist < x_dist){
		entity->move_hard(sf::Vector2f(0, y_dist*y_dir));
	}
	else{
		entity->move_hard(sf::Vector2f(x_dist*x_dir, y_dist*y_dir));
	}
	entity->move_hard(sf::Vector2f(0, -GRAVITY));
	entity->update_visual();

}
void CollisionManager::collision_response( Entity* t, Entity* entity){
	//determine if your above, below, to the left or to the right of the fucking thing 	
	sf::FloatRect tile = t->getRect()->getGlobalBounds();
	sf::FloatRect ent = entity->getRect()->getGlobalBounds();

	//gotta do something about them top right corners too right ???
	//im pretty sure the origin is top right corner
	//with that in mind
	//get centre
	sf::Vector2f t_centre = sf::Vector2f(
	tile.left + (t->getRect()->getGlobalBounds().width/2),
	tile.top + (t->getRect()->getGlobalBounds().height/2)	
		);
	sf::Vector2f e_centre = entity->getPosition();
	//ent.x = ent.x + (entity->getRect()->getGlobalBounds().width/2);
	//ent.y = ent.y + (entity->getRect()->getGlobalBounds().height/2);

	float y_dist=0;
	int x_dir =1;//this is needed to etermine in which direction to push, left right or up/down
	int y_dir =1;
	//check vertical
	if(e_centre.y > t_centre.y){//below, since 0  0 is top kek
		//gotta get the bot y of ent 
		//top y of tile 
		//distance between them
		y_dist = tile.top + tile.height - ent.top ;
		y_dir = 1;
		//std::cout<<" below "<<y_dist<<" \n";

	}
	else{//above
		y_dist = ent.top + ent.height - tile.top - GRAVITY;
		y_dir = -1;
		//std::cout<<" above "<<y_dist<<" \n";
	}
	//check horizontal
	float x_dist = 0;
	if(e_centre.x > t_centre.x){//to the right
		x_dir = 1;
		x_dist = tile.left + tile.width - ent.left;
		//std::cout<<" right "<<x_dist<<" \n";
	}
	else{//left
		x_dir = -1;
		x_dist =ent.left + ent.width - tile.left;
		//std::cout<<" left "<<x_dist<<" \n";
	}

	if(x_dist < y_dist){
		entity->move_hard(sf::Vector2f(x_dist*x_dir, 0));
	}
	else if(y_dist < x_dist){
		entity->move_hard(sf::Vector2f(0, y_dist*y_dir));
	}
	else{
		entity->move_hard(sf::Vector2f(x_dist*x_dir, y_dist*y_dir));
	}
	entity->move_hard(sf::Vector2f(0, -GRAVITY));
	entity->update_visual();

}
Entity* CollisionManager::check_collision_ents(Entity* ent){
	std::vector<Entity*>::iterator begin_ent = EntityManager::instance()->get_beign();
	std::vector<Entity*>::iterator end_ent = EntityManager::instance()->get_end();
	//for every entity
	for(begin_ent; begin_ent != end_ent; begin_ent++){
		if(ent != (*begin_ent))
			if(ent->getRect()->getGlobalBounds().intersects(
					(*begin_ent)->getRect()->getGlobalBounds())){
						return (*begin_ent);
			}
	}
	return 0;
}