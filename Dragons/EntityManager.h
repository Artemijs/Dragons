#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Entity.h"
#include <vector>
class EntityManager{
private:
	std::vector<Entity*>* m_all_entities;
	int m_entities_count;
	static EntityManager* m_instance;
	EntityManager();
	~EntityManager();
public:
	static EntityManager* instance();
	int addEntity(Entity *ent);
	Entity* getEntity(int entId);
};
#endif