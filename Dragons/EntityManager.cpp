#include "EntityManager.h"
#include <assert.h>
#include "Math.h"
EntityManager* EntityManager::m_instance=0;
EntityManager::EntityManager(){
	m_all_entities = new std::vector<Entity*>();
	m_entities_count=0;
}
EntityManager::~EntityManager(){
	//not beign called prob
	std::cout<<" deleting ent manager \n";
	/*for (unsigned i = 0; i < m_all_entities->size(); i++)
	{
		delete (*m_all_entities)[i];
	}*/
	//delete[] m_all_entities;
	//delete m_instance;
}
void EntityManager::update(float deltaTime){
	std::vector<Entity*>::iterator it = m_all_entities->begin();
	std::vector<Entity*>::iterator end = m_all_entities->end();
	for(; it != end; it++){
		(*it)->update(deltaTime);
	}
}
void EntityManager::draw(sf::RenderWindow* window){
	std::vector<Entity*>::iterator it = m_all_entities->begin();
	std::vector<Entity*>::iterator end = m_all_entities->end();
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
Entity* EntityManager::getEntity(int entId){
	return (*m_all_entities)[entId];
}
bool EntityManager::in_range(int myId, int targetId, float range){
	sf::Vector2f one = (*m_all_entities)[myId]->getPosition();
	sf::Vector2f two = (*m_all_entities)[targetId]->getPosition();

	return (math_get_distance(one, two)<range);
}
void EntityManager::move_towards(int myId, int targetId){
	Entity* one = (*m_all_entities)[myId];
	sf::Vector2f two = (*m_all_entities)[targetId]->getPosition();
	one->move(math_get_direction(one->getPosition(), two));
}
bool EntityManager::in_range(int myId, sf::Vector2f* pos, float range){
	sf::Vector2f one = (*m_all_entities)[myId]->getPosition();

	return (math_get_distance(one, (*pos))<range);
}
void EntityManager::move_towards(int myId, sf::Vector2f* m_pos){
	assert(true);
}
sf::Vector2f EntityManager::get_direction(int myId, int targetId){
	sf::Vector2f one = (*m_all_entities)[myId]->getPosition();
	sf::Vector2f two = (*m_all_entities)[targetId]->getPosition();
	return math_get_direction(one, two);
	
}
sf::Vector2f EntityManager::get_direction(sf::Vector2f pos, int targetId){
	return math_get_direction(pos, (*m_all_entities)[targetId]->getPosition());
}
std::vector<Entity*>::iterator EntityManager::get_beign(){
	return m_all_entities->begin();
}
std::vector<Entity*>::iterator EntityManager::get_end(){
	return m_all_entities->end();
}