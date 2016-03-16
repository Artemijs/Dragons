#ifndef FLAG_H
#define FLAG_H

#include "Entity.h"
#include "BaseState.h"
class Flag{
public:
	std::string name;
	Entity m_entity;
	BaseState m_newState;

};
#endif


