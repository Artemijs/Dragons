#ifndef PLAYERCONTAINER_H
#define PLAYERCONTAINER_H
#include "Dragon.h"
/*
	this class is solely for the purpose of using human and his pets
	and having access to both and for one to the other
	so that i can later create a PlayerMAnager if needed that will contain both players
	and their pets
*/
class PlayerContainer{
public:
	PlayerContainer(){}
	PlayerContainer(Human* h, Dragon* d);
	Human* HUMAN;
	Dragon* PET;
};
#endif