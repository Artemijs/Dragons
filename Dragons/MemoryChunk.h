/*
currently this is super insecure, like you can fuck shit up so bad if you try to use memory out of bounds
it wont giff an error straight away 
it will create an error the cause of which you will never ever find
USE WITH CAUTION RUSKI
in case i forget, the purpose of this calss is to :
preload memory for use 
delete memory at the end 
be able to overwrite the said memory 
essentially i need it to make arguments array that are passed to the state functions
because calling new/delete on the go can be expensive... right ?
also singleton because i need to be able to access it from anywhere, aswell as there may
only be one of its kind, wouldnt want to make 2 of these large cunks of memory


eventually this will use linked list of my own making but i dont have the time for that right now 
*/

#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H

class MemoryChunk{
private:
	MemoryChunk();
	~MemoryChunk();
	static MemoryChunk* m_instance;
	float* m_all_memory;
	int m_memory_max;//ho many cells to pre load in the array ( lenght of m_all_memory array )
	int m_free_memory;// an index to where the used memory ends and free memory begins
	//resets to 0 every frame
	//all memory must be used every frame, else the data will be overwritten

public:
	static MemoryChunk* instance();
	void reset(){m_free_memory = 0;}
	float* getArray();
	void changeIndexBy(int offset){ m_free_memory+=offset;}
};
#endif