#include "Math.h"
#include "Macros.h"
#include "Level.h"
float math_get_lenght(sf::Vector2f vector){
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}
sf::Vector2f math_normalize(sf::Vector2f vector){
	float len = math_get_lenght(vector);
	return sf::Vector2f(vector.x/len, vector.y/len);	
}
sf::Vector2f math_get_direction(sf::Vector2f one, sf::Vector2f two){
	if(one == two) return VECTOR_ZERO;
	return math_normalize(two-one);
}
float math_get_distance(sf::Vector2f one, sf::Vector2f two){
	return math_get_lenght(two-one);
}
int math_random_range(int max, int min){
	return std::rand()%(max-min)+min;
}
TILE_NEIGHBORS math_get_TN_from_dir(sf::Vector2f dir){
	TILE_NEIGHBORS tn = TILE_NEIGHBORS::NONE;
	bool vert = false;
	sf::Vector2f abs_dir = sf::Vector2f(std::abs(dir.x), std::abs(dir.y));
	bool axis = (abs_dir.x > abs_dir.y);
	//AXIS = TRUE horizontal else vertical
	if(axis){
		if(dir.x>0)
			tn = TILE_NEIGHBORS::RIGHT;
		else tn = TILE_NEIGHBORS::LEFT;
	}else{
		if(dir.y>0)
			tn = TILE_NEIGHBORS::DOWN;
		else tn = TILE_NEIGHBORS::UP;
	}
	return tn;
}