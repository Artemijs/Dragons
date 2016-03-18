#include "FlagPool.h"
FlagPool* FlagPool::m_instance =0;
FlagPool::FlagPool(){
	m_allFlags = new std::vector<Flag>();
}
FlagPool::~FlagPool(){
	delete m_allFlags;
	delete m_instance;
}
FlagPool* FlagPool::instance(){
	if(m_instance == 0)
		m_instance = new FlagPool();
	return m_instance;
}
//this right here is very innefficient, since after every erase it then resorts the array
//since its just a prototype it will have to do, but when im doing it properly i will need to create my own single likned list
void FlagPool::update(float deltaTime){
	
	std::vector<Flag>::iterator begin = m_allFlags->begin();
	std::vector<Flag>::iterator end = m_allFlags->end();
	while(begin != end){
		(*begin).m_target->setState((*begin).m_newState, (*begin).args);
		//begin = m_allFlags->erase(begin);
		begin++;
	}
	
	m_allFlags->erase(m_allFlags->begin(), m_allFlags->end());
}
void FlagPool::addFlag(Flag f){
	m_allFlags->push_back(f);
}