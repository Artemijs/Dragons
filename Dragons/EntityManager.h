#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Dragon.h"
#include <vector>

class EntityManager{
private:
	std::vector<Entity*>* m_all_entities;
	int m_entities_count;
	static EntityManager* m_instance;
	EntityManager();
	
public:
	~EntityManager();
	static EntityManager* instance();
	int addEntity(Entity *ent);
	Entity* getEntity(int entId);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	bool in_range(int myId, int targetId, float range);
	bool in_range(int myId, sf::Vector2f* m_pos, float range);
	void move_towards(int myId, int targetId);
	void move_towards(int myId, sf::Vector2f* m_pos);
	sf::Vector2f get_direction(int myId, int targetId);
	sf::Vector2f get_direction(sf::Vector2f pos, int targetId);
	std::vector<Entity*>::iterator get_beign();
	std::vector<Entity*>::iterator get_end();
};
#endif