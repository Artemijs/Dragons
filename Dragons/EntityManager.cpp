#include "EntityManager.h"
EntityManager* EntityManager::m_instance=0;
EntityManager::EntityManager(){
	m_all_entities = new std::vector<Entity*>();
	m_entities_count=0;
}
EntityManager::~EntityManager(){
	for (int i = 0; i < m_all_entities->size(); i++)
	{
		delete (*m_all_entities)[i];
	}
	delete m_all_entities;
	delete m_instance;
}
void EntityManager::update(float deltaTime){
	std::vector<Entity*>::iterator it = m_all_entities->begin();
	std::vector<Entity*>::iterator end = m_all_entities->end();
	for(; it != end; it++){
		//(*it)->update(deltaTime);
	}
}
EntityManager* EntityManager::instance(){
	if(m_instance == 0)
		m_instance = new EntityManager();
	return m_instance;
}
int EntityManager::addEntity(Entity *ent){
	m_all_entities->push_back(ent);
	m_entities_count++;
	return m_entities_count;
}
Entity* EntityManager::getEntity(int entId){
	return (*m_all_entities)[entId];
}