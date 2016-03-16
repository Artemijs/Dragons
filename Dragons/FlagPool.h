#ifndef FLAGPOOL_H
#define FLAGPOOL_H
#include "Flag.h"
class FlagPool{
private:
	std::vector<Flag>* m_allFlags;
	static FlagPool* m_instance;
	FlagPool();
	~FlagPool();
public:
	static FlagPool* instance();
	void update(float deltaTime);
	void addFlag(Flag f);

};

#endif