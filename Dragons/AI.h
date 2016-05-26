#ifndef AI_H
#define AI_H
#include "Net.h"
typedef vector<double> Item;
class AI{
private:
	Net m_personality;
	vector<double> m_memory;
public:
	AI();
	void trainAI();
};
#endif
