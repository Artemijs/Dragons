#ifndef AI_H
#define AI_H
#include "Net.h"
#include "Entity.h"
typedef vector<double> Item;
class AI{
private:
	Net m_personality;
	vector<double> m_memory;
public:
	AI();
	void trainAI();
};
class BasicAI{
	/*
		this class basically takes a target and moves towards it
		once in range uses ability_lance
		and that is it
	*/
private:
public:
	BasicAI(){}
	~BasicAI(){}
	void new_move(Entity* me, Entity* target);
};
#endif
