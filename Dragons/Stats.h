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
class Stats{
private:
	//your 3 basic stats
	float m_int;//inteligence
	float m_str;//strenght
	float m_agi;//agility
	//things that your 3 basic stats give uou
	float m_int_to_mana;//max mana
	float m_int_to_regen;//mana regen per second
	float m_str_to_health;//max hp
	float m_str_to_regen;//hp regen
	float m_agi_to_armor;
	float m_agi_to_att_speed;

	//your actual in game stats
	float m_damage; // dmg = base_dmg+whatever
	float m_armor;// = base_armor +m_agi*agi2armor
	float m_attack_speed;// = base_sattack_spid + m_agi*m_ag2aspeed
	float m_hp_regen;// = m_str*m_str2hp_regen
	float m_current_hp;// = base_hp + m_str*str_2_hp
	float m_max_hp;// = base_hp + m_str*str_2_hp
	float m_mana_regen;// =  m_int*str_2_regen
	float m_current_mana;// = base_mana + m_str*str_2_mana
	float m_max_mana;// = base_mana + m_str*str_2_mana
	float m_move_speed;
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
	Stats(float dmg, float intel, float str, float agi, float int2mana, float int2mreg,
		float str2hp, float str2hpreg, float agi2armor, float agi2attSpeed, float movspid );
	
};
#endif 