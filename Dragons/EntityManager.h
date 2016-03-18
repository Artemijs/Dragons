#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Dragon.h"
#include <vector>
class EntityManager{
private:
	std::vector<Dragon*>* m_all_entities;
	int m_entities_count;
	static EntityManager* m_instance;
	EntityManager();
	~EntityManager();
public:
	static EntityManager* instance();
	int addEntity(Dragon *ent);
	Dragon* getEntity(int entId);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
};
#endif