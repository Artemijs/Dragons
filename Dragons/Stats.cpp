#include "Stats.h"
//NOTE: ATTACKSPEED MUST DECRESE TO INCREASE, because it is the animation time, the smaller the number, the shorter the animation, the faster you hit
const float Stats::BASE_DAMAGE = 40;
const float Stats::BASE_HEALTH = 600;
const float Stats::BASE_MANA = 300;
const float Stats::BASE_INT = 1;
const float Stats::BASE_STR = 1;
const float Stats::BASE_AGI = 1;
const float Stats::BASE_ARMOR = 0.1;
const float Stats::BASE_ATTACK_SPEED = 1.5f;
const float Stats::MAX_ATTACK_SPEED = 0.2;
const float Stats::BASE_MOVE_SPEED = 3;
const float Stats::MAX_MOVE_SPEED = 10;
Stats::Stats(float dmg, float intel, float str, float agi, float int2mana, float int2mreg,
	float str2hp, float str2hpreg, float agi2armor, float agi2attSpeed, float movspid):
	m_int_to_mana(int2mana),
	m_int_to_regen(int2mreg),
	m_str_to_health(str2hp),
	m_str_to_regen(str2hpreg),
	m_agi_to_armor(agi2armor),
	m_agi_to_att_speed(agi2attSpeed){
	
	m_int = BASE_INT + intel;
	m_str = BASE_STR + str;
	m_agi = BASE_AGI + agi;

	//your actual in game stats
	m_damage = dmg+BASE_DAMAGE;
	m_armor = BASE_ARMOR + m_agi*m_agi_to_armor;
	m_attack_speed = BASE_ATTACK_SPEED - m_agi*m_agi_to_att_speed;
	m_hp_regen = m_str*m_str_to_regen;
	m_current_hp = BASE_HEALTH + m_str*m_str_to_health;
	m_max_hp = m_current_hp;
	m_mana_regen = m_int * m_int_to_regen;
	m_current_mana = m_int*m_int_to_mana + BASE_MANA;
	m_max_mana = m_current_mana;
	m_move_speed = BASE_MOVE_SPEED + movspid;

}
Stats::Stats(){
	//your 3 basic stats
	m_int = BASE_INT;//inteligence
	m_str = BASE_STR;//strenght
	m_agi = BASE_AGI;//agility
	//things that your 3 basic stats give uou
	m_int_to_mana = 5;//max mana
	m_int_to_regen = 0.1;//mana regen per second
	m_str_to_health = 10;//max hp
	m_str_to_regen = 0.1;//hp regen
	m_agi_to_armor = 0.005;
	m_agi_to_att_speed = 0.007;

	//your actual in game stats
	m_damage = BASE_DAMAGE;
	m_armor = BASE_ARMOR + m_agi*m_agi_to_armor;
	m_attack_speed = BASE_ATTACK_SPEED - m_agi*m_agi_to_att_speed;
	m_hp_regen = m_str*m_str_to_regen;
	m_current_hp = BASE_HEALTH + m_str*m_str_to_health;
	m_max_hp = m_current_hp;
	m_mana_regen = m_int * m_int_to_regen;
	m_current_mana = m_int*m_int_to_mana + BASE_MANA;
	m_max_mana = m_current_mana;
	m_move_speed = BASE_MOVE_SPEED;
}