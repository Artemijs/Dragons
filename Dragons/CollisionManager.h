#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "EntityManager.h"
#include "Level.h"
class CollisionManager{
private:
public:
	CollisionManager(){}
	void check_tiles();
	void collision_response(Tile* t, Entity* ent);
};
#endif