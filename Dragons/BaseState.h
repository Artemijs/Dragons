#ifndef BASESTATE_H
#define BASESTATE_H
typedef void (*fptr)(int id, float args[]);
/*
class BaseState{
public:
	BaseState(){
	}
	//void action(int id, float args[]);
};
class MovingState: public BaseState{
public :
	void action(int id, float args[]);

};*/
void action_move(int id, float args[]);
#endif