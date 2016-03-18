#include "MemoryChunk.h"
MemoryChunk* MemoryChunk::m_instance = 0;
MemoryChunk* MemoryChunk::instance(){
	if(m_instance == 0)
		m_instance = new MemoryChunk();
	return m_instance;
}
MemoryChunk::MemoryChunk(){
	m_memory_max = 10;
	m_all_memory = new float[m_memory_max]();
	m_free_memory = 0;
}
MemoryChunk::~MemoryChunk(){
	delete m_all_memory;
}
float* MemoryChunk::getArray(){
	return &(m_all_memory[m_free_memory]);
}