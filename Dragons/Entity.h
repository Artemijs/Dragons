
#ifndef ftrp
typedef void (*fptr)(int id, float args[]);
#endif

#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp" 
#include <iostream>
#include "Ability.h"
#include "Stats.h"
//#include "BaseState.h"

enum EntityState{
	IDLE,
	CASTING,
	DEAD
};
class Entity{
protected:
	int m_current_tile;
	EntityState m_state;//depricated
	EntityState m_nextState;
	sf::RectangleShape m_rect;
	int m_id;//index in the all entities array
	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	Stats* m_stats;
	std::vector<Ability*>* m_all_abilities;
	int m_selected_target;//incase of lock on abilities
public:
	Entity(int id);
	EntityState getState(){return m_state;}
	bool set_state(EntityState newState);
	void setDirection(sf::Vector2f newDir);
	sf::Vector2f getDirection(){return m_direction;}
	sf::Vector2f getPosition(){return m_position;}
	void setPosition(sf::Vector2f newPos);
	void move_hard(sf::Vector2f dist);
	void take_damage(float dmg);
	void set_id(int id){
		m_id = id;
	}
	int get_id(){return m_id;}
	sf::RectangleShape* getRect();
	virtual ~Entity();
	virtual void update(float deltaTime) =0;
	virtual void update_visual() = 0;
	virtual void draw(sf::RenderWindow* window) =0;
	virtual void move(int newTile);
	virtual void use_ability(int target, int aIndex) = 0;
	void respawn(sf::Vector2f pos);
	void set_tile(int t){m_current_tile = t;}
	int get_tile(){return m_current_tile;}
	void next_action();
	Stats* get_stats(){return m_stats;}
	sf::Vector2f get_HeightWidth();
};

#endif