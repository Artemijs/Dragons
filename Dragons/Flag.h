#ifndef FLAG_H
#define FLAG_H

#include "Entity.h"
#include "State.h"
struct Flag{
	std::string text;
	Entity* m_target;//target
	fptr m_newState;
};
/*class Flag{
public:
	std::string name;
	Entity m_target;//target
	fptr m_newState;

};*/
#endif


