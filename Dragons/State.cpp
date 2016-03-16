#include "State.h"
void action_move(int id, float args[]){
	//this state continually moves a thing 
	//args include:
		//x dir
		//y dir
	std::cout<<"moving \n";
	Entity* ent = EntityManager::instance()->getEntity(id);
	ent->setPosition(args[0]+ent->getPosition().x, args[1]+ent->getPosition().y);
	
}
void action_idle(int id, float args[]){
	//do nothing
	std::cout<<"idling \n";
}