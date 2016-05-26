#include "AI.h"
void getTarget(int i ,vector<double> & target);
AI::AI(){
	vector<unsigned> topology;
	topology.push_back(1);
	topology.push_back(10);
	topology.push_back(3);
	//in : physical status from basic needs, gender, type
	//out is idk
	m_personality = Net(topology);
	m_memory.push_back(1);
	m_memory.push_back(0);
	m_memory.push_back(0);
	m_memory.push_back(0);

	trainAI();
}
int filtr(vector<double> & res){
	for(int i = 0; i <res.size(); i++){
		if(res[i] > 0.5) return i;
	}
}
void AI::trainAI(){
	for(int i =0; i < 2000; ++i){
		vector<double> inputvals;
		inputvals.push_back(i%4);//index
		/*inputvals.push_back(m_memory[0]);
		inputvals.push_back(m_memory[1]);
		inputvals.push_back(m_memory[2]);
		inputvals.push_back(m_memory[3]);
		*/vector<double> resultvals;

		m_personality.feedForward(inputvals);
		m_personality.getResults(resultvals);
		vector<double> target;
		getTarget(i, target);
		int res = filtr(resultvals);
		std::cout<<" target "<<filtr(target)<<" result "<<res<<"\n";
		m_personality.backProp(target);
	}
	system("PAUSE");
}

double round(double nr){
	if(nr >=0.5)
		nr = 1;
	if(nr<0.5 && nr >=0)
		nr = 0;
	if(nr <0 && nr >= -0.5)
		nr = 0;
	if(nr > -1 && nr < -0.5)
		nr = -1;
	return nr;
}
void getTarget(int i, vector<double> & target){
	int nr = i%4;
	for(int i = 0 ; i < 4; i++){
		target.push_back(0);
	}
	if(nr == 3) nr = 2;
	target[nr] = 1;
	//if(nr == 0) target.push_back(0.5);
	//if(nr == 4) target.push_back(1);
	//else target.push_back(0);
}