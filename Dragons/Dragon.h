/*
The dragon
It can do the following things:
walk
jump
fly

WALK
	walking speed 
	walking direction
JUMP
	gravity
	jump height
	jump direction
FLY
	I can use the hoverboard physics,
	where the angle determines the speed
	as if it were to slide down an invisible plain
	that you have contorol over

	  float ang = Mathf.Acos(
                Vector3.Dot(hit.normal, transform.TransformDirection(Vector3.up)) /
                hit.normal.magnitude * transform.TransformDirection(Vector3.up).magnitude);
            //
            //Debug.Log(hit.normal);
            float f = 0.1f * 9 * Mathf.Sin(ang);
            Vector3 v1 = new Vector3(-hit.normal.z, 0, hit.normal.x);
            //Debug.Log(v1);
            Vector3 slopeDir = Vector3.Cross(v1, hit.normal);
			 gameObject.rigidbody.AddForce(slopeDir * f *-1, ForceMode.Force);
	so...
	Flight speed
	Turn speed

	Not to mention all this shit should be controlled by states ??
	So i will have this dragon class that will store its stats
	So it shouldnt have any member functions?
	I might have ufcked up a litle bit here
	IT at the very least needs an update
	To move the sprite along and apply state changes
	so lets try some scenarios:
	STATE: MOVE
	your moving
	STATE: JUMP
	you gifff yourself some upward velocity and
	now your off the ground, is your state falling? in air? flying ?
	assuming its flying 
	STATE : FLYING
	i oculd make it so that its simply an arc
	jumping could be propelling into the air, the same way you would propel while flying
	as such i believe i need to do flying first and foremost
*/

#ifndef DRAGON_H
#define DRAGON_H
#include "Entity.h"
#include "SFML\Graphics.hpp"
class Dragon: public Entity{
private:
	
	sf::CircleShape m_cF;
	sf::CircleShape m_cB;
	float m_moveSpeed;
	float m_angle;
public:
	Dragon(int id);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	void rotate(float ang);
	void move(sf::Vector2f dir);
	void use_ability(int target, int aIndex);
	void setPosition(sf::Vector2f newPos);
};
#endif
/*
hunting
swimming
hair dryer


*/