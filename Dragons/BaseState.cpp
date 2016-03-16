#include "BaseState.h"
#include "EntityManager.h"
/*
void MovingState::action(int id, float args[]){
	//this state continually moves a thing 
	//args include:
		//x dir
		//y dir
	Entity* ent = EntityManager::instance()->getEntity(id);
	ent->setPosition(args[0]+ent->getPosition().x, args[1]+ent->getPosition().y);
	
}
*/
void action_move(int id, float args[]){
	//this state continually moves a thing 
	//args include:
		//x dir
		//y dir
	Entity* ent = EntityManager::instance()->getEntity(id);
	ent->setPosition(args[0]+ent->getPosition().x, args[1]+ent->getPosition().y);
	
}

