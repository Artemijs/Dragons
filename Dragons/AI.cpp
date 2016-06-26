#include "AI.h"
#include "Math.h"
#include "Level.h"
#include "Macros.h"
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












void BasicAI::new_move(Entity* me, Entity* target){
	int ability_index = 0;
	//get direction
	sf::Vector2f dir = math_get_direction(me->getPosition(), target->getPosition());
	//change direction to move
	TILE_NEIGHBORS direction = math_get_TN_from_dir(dir);
	bool inine=((dir.x < 0.1 && dir.x> -0.1) || (dir.y < 0.1 && dir.y > -0.1));
	if(inine){
		float dist = math_get_distance(me->getPosition(), target->getPosition());
		if(direction == TILE_NEIGHBORS::RIGHT || direction == TILE_NEIGHBORS::LEFT){
			dist /= TILE_WIDTH;
		}
		else{
			dist /= TILE_HEIGHT;
		}
		if(dist < 3){
			ability_index = 2;
		}
	}
	me->use_ability(direction, ability_index);
}