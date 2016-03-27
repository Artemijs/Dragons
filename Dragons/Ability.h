/*||Ryanair|Aerlingus|
|-----------------------------------------------|
|Total|615.92 |621.92|
|Bags|40*2|35*2|
|Total no bag|536|552|
|Ruski|136|139|
|Us|160|161|
 -----------------------------------------------
Ryanair:
Sun 5th Jun 06:50 - 09:30 FR 3100
Sun 12th Jun 14:10 - 14:50 FR 3103

Aerlingus
Sun, 5 Jun 05:55 - 08:40 EI 602
Sun, 12 Jun 20:35 - 21:20 EI 611
*/

#ifndef ABILITY_H
#define ABILITY_H
#include "SFML\Graphics.hpp"
// DONT FORGET, HOW TO BUFFS AND DEBUFFS
//dont foget ability factory or some shit
enum Ability_State{
	READY,//or idle
	CHARGING,//when play the animation
	ACTION,//apply the damage
	COOLDOWN//count the cooldown
};
class Ability{
protected:
	bool m_alive;
	float m_damage;//THIS SHOULD BE SOMETHING ELSE, something that includes a debuffs and shit 
	float m_cast_speed_max;//delay before things happen, aka animation speed
	float m_cast_speed_time;
	float m_mana_cost;
	float m_cool_down_max;
	float m_cool_down_current;
	int m_my_id;
	float m_range;//of spell
	//sf::Vector2f* m_my_position;//position of the caster
	int m_target_id;// location in the all entities array 
	sf::Vector2f* m_target;//strictly for aoe spells, because they can be ground targetted
	Ability_State m_state;
public :
	Ability(){}
	~Ability(){}
	Ability(int myid);
	virtual void cast(int targetId) = 0;
	virtual void cast(sf::Vector2f* target) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	float get_damage();
	float get_mana_cost();
	float get_cooldown_max();
	float get_cast_speed();
	int get_target();
	float get_range();
	sf::Vector2f* get_target_ptr();
	void set_damage(float dmg);
	void set_mana_cost(float mana_cost);
	void set_cooldown_max(float cooldown);
	void set_cast_speed(float cas_spd);
	void set_target(int targetId);
	void set_target(sf::Vector2f* target);
	void set_range(float range);

};
class Projectile{
private:
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	bool m_alive;
	int m_target_id;//if hoing get a direction from you to it
public:
	Projectile();
	Projectile(sf::Vector2f velocity);
	bool get_alive(){return m_alive;}
	void set_alive(bool live){m_alive = live;}
	void update(float deltaTime, float speed);
	void draw(sf::RenderWindow* window);
	void set_position(sf::Vector2f pos);
	void set_velocity(sf::Vector2f vel);
	void set_targetId(int target){m_target_id = target;}

};
class Ability_Ranged: public Ability{
	/*
	any ability that throws something
	*/
private:
	float m_projectile_speed;
	Projectile m_projectile;
public:
	Ability_Ranged(int myId);
	~Ability_Ranged(){}
	float get_projectile_speed();
	//use this for homing projectiles
	void cast(int targetId);
	//use this for skillshots and aoe spells
	void cast(sf::Vector2f* target);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
};
class Ability_AOE: public Ability{
/*
	an area of effect that simply triggers either where you click or on you
	uses m_target instead of m_target_id
*/
protected:
	float m_aoe_range;
	float m_damage_delay_max;//think torrent or sunstrike, 
	//theres an animation time and then theres damage delay
	float m_damage_delay_time;
	sf::RectangleShape m_shape;
public:
	Ability_AOE(int myId);
		//use this for homing projectiles
	void cast(int targetId) = 0;
	//use this for skillshots and aoe spells
	void cast(sf::Vector2f* target) = 0;
	void update(float deltaTime) = 0;
	void draw(sf::RenderWindow* window) = 0;
};
/*
	buff/debuff - will be made a seperaye thing so they can be dispellable and shit
	because every buff comes from ability or aura but not every ability or aura has a buff/debuff
*/
class Ability_Aura: public Ability{
/*
	an ability that affects self and/or anyone around self
	can be buff to self or debuff to others

	the way it can work is set the manacost and cooldown to 0
	so it will be auto casted every frame

	honestly i think ill have to make a seperate class for every type of aura
	but ill do that.. in the next.. sprint rofl, im behind by like 10 days on this sprint
	not to mention how badly i fucked up my stories, ended up not even doing 
	whats on th sprint. But whatever, rant over
*/
};

#endif