#include "Stats.h"
#include <iostream>
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
	float str2hp, float str2hpreg, float agi2armor, float agi2attSpeed, float movspid){
	
	m_all_stats[Stat_Type::INT_2_MANA] = int2mana;
	m_all_stats[Stat_Type::INT_2_REGEN] = int2mreg;
	m_all_stats[Stat_Type::STR_2_HP] = str2hp;
	m_all_stats[Stat_Type::STR_2_REGEN] = str2hpreg;
	m_all_stats[Stat_Type::AGI_2_ARMOR] = agi2armor;
	m_all_stats[Stat_Type::AGI_2_ATT_SPEED] = agi2attSpeed;

	m_all_stats[Stat_Type::INT] = BASE_INT + intel;
	m_all_stats[Stat_Type::STR] = BASE_STR + str;
	m_all_stats[Stat_Type::AGI] = BASE_AGI + agi;

	//your actual in game stats, which can be affected by buffs/debuffs
	m_all_stats[Stat_Type::DAMAGE] = dmg + BASE_DAMAGE;
	m_all_stats[Stat_Type::ARMOR] = BASE_ARMOR + m_all_stats[Stat_Type::AGI] * m_all_stats[Stat_Type::AGI_2_ARMOR];
	m_all_stats[Stat_Type::HP_REGEN] = m_all_stats[Stat_Type::STR] * m_all_stats[Stat_Type::STR_2_REGEN];
	m_all_stats[Stat_Type::MAX_HP] = BASE_HEALTH + m_all_stats[Stat_Type::STR] * m_all_stats[Stat_Type::STR_2_HP];
	//m_attack_speed = BASE_ATTACK_SPEED - m_agi*m_agi_to_att_speed;
	m_all_stats[Stat_Type::CURR_HP] = m_all_stats[Stat_Type::MAX_HP];
	m_all_stats[Stat_Type::MAX_MANA] = BASE_MANA + m_all_stats[Stat_Type::INT] * m_all_stats[Stat_Type::INT_2_MANA];
	m_all_stats[Stat_Type::CURR_MANA] = m_all_stats[Stat_Type::MAX_MANA];
	m_all_stats[Stat_Type::MANA_REGEN] = m_all_stats[Stat_Type::INT] * m_all_stats[Stat_Type::INT_2_REGEN];
	m_all_stats[Stat_Type::MOVE_SPEED] = BASE_MOVE_SPEED + movspid;
}
Stats::Stats(){
	m_all_stats[Stat_Type::INT_2_MANA] = 5;
	m_all_stats[Stat_Type::INT_2_REGEN] = 0.1;
	m_all_stats[Stat_Type::STR_2_HP] = 10;
	m_all_stats[Stat_Type::STR_2_REGEN] = 0.1;
	m_all_stats[Stat_Type::AGI_2_ARMOR] = 0.005;
	m_all_stats[Stat_Type::AGI_2_ATT_SPEED] = 0.007;

	m_all_stats[Stat_Type::INT] = BASE_INT;
	m_all_stats[Stat_Type::STR] = BASE_STR;
	m_all_stats[Stat_Type::AGI] = BASE_AGI;

	//your actual in game stats, which can be affected by buffs/debuffs
	m_all_stats[Stat_Type::DAMAGE] = BASE_DAMAGE;
	m_all_stats[Stat_Type::ARMOR] = BASE_ARMOR + m_all_stats[Stat_Type::AGI] * m_all_stats[Stat_Type::AGI_2_ARMOR];
	m_all_stats[Stat_Type::HP_REGEN] = m_all_stats[Stat_Type::STR] * m_all_stats[Stat_Type::STR_2_REGEN];
	m_all_stats[Stat_Type::MAX_HP] = BASE_HEALTH + m_all_stats[Stat_Type::STR] * m_all_stats[Stat_Type::STR_2_HP];
	//m_attack_speed = BASE_ATTACK_SPEED - m_agi*m_agi_to_att_speed;
	m_all_stats[Stat_Type::CURR_HP] = m_all_stats[Stat_Type::MAX_HP];
	m_all_stats[Stat_Type::MAX_MANA] = BASE_MANA + m_all_stats[Stat_Type::INT] * m_all_stats[Stat_Type::INT_2_MANA];
	m_all_stats[Stat_Type::CURR_MANA] = m_all_stats[Stat_Type::MAX_MANA];
	m_all_stats[Stat_Type::MANA_REGEN] = m_all_stats[Stat_Type::INT] * m_all_stats[Stat_Type::INT_2_REGEN];
	m_all_stats[Stat_Type::MOVE_SPEED] = BASE_MOVE_SPEED;
}
void Stats::take_damage(float damage){
	m_all_stats[Stat_Type::CURR_HP]  -= damage *(1-m_all_stats[Stat_Type::ARMOR]);
	std::cout<<"hp "<<m_all_stats[Stat_Type::CURR_HP]<<"\n";
}
void Stats::lose_mana(float mana){
	m_all_stats[Stat_Type::CURR_MANA] -= mana;
	std::cout<<"mana "<<m_all_stats[Stat_Type::CURR_MANA]<<"\n";
}
const float Stats::get_stat(Stat_Type st){
	return m_all_stats[st];
}
void Stats::reset(){
	m_all_stats[Stat_Type::MAX_HP] = BASE_HEALTH + m_all_stats[Stat_Type::STR] * m_all_stats[Stat_Type::STR_2_HP];
	m_all_stats[Stat_Type::CURR_HP] = m_all_stats[Stat_Type::MAX_HP];
	m_all_stats[Stat_Type::MAX_MANA] = BASE_MANA + m_all_stats[Stat_Type::INT] * m_all_stats[Stat_Type::INT_2_MANA];
	m_all_stats[Stat_Type::CURR_MANA] = m_all_stats[Stat_Type::MAX_MANA];
}