#include "EntityManager.h"
#include <assert.h>
EntityManager* EntityManager::m_instance=0;
EntityManager::EntityManager(){
	m_all_entities = new std::vector<Dragon*>();
	m_entities_count=0;
}
EntityManager::~EntityManager(){
	//not beign called prob
	std::cout<<" deleting ent manager \n";
	for (unsigned i = 0; i < m_all_entities->size(); i++)
	{
		delete (*m_all_entities)[i];
	}
	delete m_all_entities;
	//delete m_instance;
}
void EntityManager::update(float deltaTime){
	std::vector<Dragon*>::iterator it = m_all_entities->begin();
	std::vector<Dragon*>::iterator end = m_all_entities->end();
	for(; it != end; it++){
		(*it)->update(deltaTime);
	}
}
void EntityManager::draw(sf::RenderWindow* window){
	std::vector<Dragon*>::iterator it = m_all_entities->begin();
	std::vector<Dragon*>::iterator end = m_all_entities->end();
	for(; it != end; it++){
		(*it)->draw(window);
	}
}
EntityManager* EntityManager::instance(){
	if(m_instance == 0)
		m_instance = new EntityManager();
	return m_instance;
}
int EntityManager::addEntity(Dragon *ent){
	m_all_entities->push_back(ent);
	m_entities_count++;
	return m_entities_count;
}
Dragon* EntityManager::getEntity(int entId){
	return (*m_all_entities)[entId];
}
bool EntityManager::in_range(int myId, int targetId, float range){
	assert(true);
	return false;
}
void EntityManager::move_towards(int myId, int targetId){
	assert(true);
}
bool EntityManager::in_range(int myId, sf::Vector2f* m_pos, float range){
	assert(true);
	return false;
}
void EntityManager::move_towards(int myId, sf::Vector2f* m_pos){
	assert(true);
}