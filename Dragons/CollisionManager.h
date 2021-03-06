#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "EntityManager.h"
#include "Level.h"
class CollisionManager{
private:
	static CollisionManager* m_instance;
	CollisionManager(){}
public:
	static CollisionManager* instance();
	void check_tiles();
	void check_entities();
	void collision_response(Tile* t, Entity* ent);
	void collision_response(Entity* t, Entity* ent);
	Entity* check_collision_ents(Entity* ent);
};
#endif