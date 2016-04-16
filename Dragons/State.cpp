#include "State.h"
void action_move(int id, float args[]){
	//this state continually moves a thing 
	//args include:
		//x dir
		//y dir
	std::cout<<"moving \n";
	Entity* ent = EntityManager::instance()->getEntity(id);
	//ent->setPosition(sf::Vector2f(args[0]+ent->getPosition().x, args[1]+ent->getPosition().y));

//	ent->setVelocity(sf::Vector2f(args[0], args[1]));
	
}
void action_idle(int id, float args[]){
	//do nothing
	std::cout<<"idling \n";
}
void action_rotate(int id, float args[]){
	//rotate sprite
	std::cout<<" rotating \n";
	float angle = args[0];
	Entity* ent = EntityManager::instance()->getEntity(id);
	//ent->rotate(angle);
//	ent->setState(action_fly, 0);

}
void action_fly(int id, float args[]){
	std::cout<<"flying \n";
	Entity* ent = EntityManager::instance()->getEntity(id);
	float ang = ent->getRect()->getRotation();
	int dir =1;
	if(ang>0 && ang< 180){
		dir = -1;
	}
	std::cout<<"flying ";
	std::cout<<ang;
	std::cout<<"\n";
	ang = ang* (3.14/180);
	float f = 0.1f * 9 * std::sin(ang);
	sf::Vector2f slopeDir = sf::Vector2f(std::cos(ang), std::sin(ang));
//	ent->setVelocity(slopeDir*(f*10*dir));
}
/*

            Vector3 v1 = new Vector3(-hit.normal.z, 0, hit.normal.x);
            //Debug.Log(v1);
            Vector3 slopeDir = Vector3.Cross(v1, hit.normal);
			 gameObject.rigidbody.AddForce(slopeDir * f *-1, ForceMode.Force);
*/