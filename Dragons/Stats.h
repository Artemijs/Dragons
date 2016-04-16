/*
this will contain everything about the dragon worth changing for balance
right here is where a dragon becomes imba ,op or overnerfed
so it will have every stat related to balance
such as 
int - max amount of mana and manaregenpersec
str - max amount of hp and hpregen per second
agi - armor and attack speed

yes very much inspired by dota 2, woopty fucking doo, its a good way of doing shit

you will also find:
current hp/mana
max hp/mana
armor
attack dmg
attack speed
MOVE SPEED
turn speed
FlYING TURN SPEED but ill get back to flying later on 

also
int to max mana ratio
int to mana regen per second
str to max hp ratio
str to hp regen per second
agi to armor ratio
agi to attack speed ratio
AND 
primary attribute a point in which gives dmg, maybe even p stat to dmg ratio but that can be added later
yes yes yes, inspired by dota 2 i know, but its a good system
*/

#ifndef STATS_H
#define	STATS_H
enum Stat_Type{
	INT,
	STR,
	AGI,
	INT_2_MANA,
	INT_2_REGEN,
	STR_2_HP,
	STR_2_REGEN,
	AGI_2_ARMOR,
	AGI_2_ATT_SPEED,
	DAMAGE,
	ARMOR,
	HP_REGEN,
	MANA_REGEN,
	MAX_HP,
	MAX_MANA,
	CURR_HP,
	CURR_MANA,
	MOVE_SPEED

};
class Stats{
private:
	float m_all_stats[18];
public:
	static const float BASE_DAMAGE ;
	static const float BASE_HEALTH ;
	static const float BASE_MANA ;
	static const float BASE_INT ;
	static const float BASE_STR ;
	static const float BASE_AGI ;
	static const float BASE_ARMOR ;
	static const float BASE_ATTACK_SPEED ;
	static const float MAX_ATTACK_SPEED ;
	static const float BASE_MOVE_SPEED ;
	static const float MAX_MOVE_SPEED ;
	Stats();
	~Stats(){}
	Stats(float dmg, float intel, float str, float agi, float int2mana, float int2mreg,
		float str2hp, float str2hpreg, float agi2armor, float agi2attSpeed, float movspid );
	void take_damage(float damage);
	void lose_mana(float mana);
	const float get_stat(Stat_Type st);
	void reset();
	
};
#endif 