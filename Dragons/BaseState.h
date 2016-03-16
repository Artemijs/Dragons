#ifndef BASESTATE_H
#define BASESTATE_H


class BaseState{
public:
	BaseState(){
	}
	//void action(int id, float args[]);
};
class MovingState: public BaseState{
public :
	void action(int id, float args[]);

};
#endif