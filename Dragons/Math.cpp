#include "Math.h"
float math_get_lenght(sf::Vector2f vector){
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}
sf::Vector2f math_normalize(sf::Vector2f vector){
	float len = math_get_lenght(vector);
	return sf::Vector2f(vector.x/len, vector.y/len);	
}
sf::Vector2f math_get_direction(sf::Vector2f one, sf::Vector2f two){
	return math_normalize(two-one);
}
float math_get_distance(sf::Vector2f one, sf::Vector2f two){
	return math_get_lenght(two-one);
}
bool phys_basic_collision(sf::FloatRect one, sf::FloatRect two){
	return one.intersects(two);
}