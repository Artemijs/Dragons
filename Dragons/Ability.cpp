#include "Ability.h"
#include "Macros.h"
#include "EntityManager.h"
#include "Math.h"
//////////////////////////////////ability class//////////////////////
Ability::Ability(int myid): m_my_id(myid){
	//default ability
	m_alive = false;
	m_damage = 100;
	m_cast_speed_max = 0.3;//third of a second
	m_cast_speed_time=0;
	m_mana_cost = 100;
	m_cool_down_max = 6;
	m_cool_down_current = 0;
	m_range = 700*DUNIT;
	m_target_id = -1;
	m_target = 0;
	m_state = Ability_State::READY;
}
float Ability::get_damage(){
	return m_damage;
}
float Ability::get_mana_cost(){
	return m_mana_cost;
}
float Ability::get_cooldown_max(){
	return m_cool_down_max;
}
float Ability::get_cast_speed(){
	return m_cast_speed_max;
}
int Ability::get_target(){
	return m_target_id;
}
float Ability::get_range(){
	return m_range;
}
sf::Vector2f* Ability::get_target_ptr(){
	return m_target;
}
void Ability::set_damage(float dmg){
	m_damage = dmg;
}
void Ability::set_mana_cost(float mana_cost){
	m_mana_cost = mana_cost;
}
void Ability::set_cooldown_max(float cooldown){
	m_cool_down_max = cooldown;
}
void Ability::set_cast_speed(float cas_spd){
	m_cast_speed_max = cas_spd;
}
void Ability::set_target(int targetId){
	m_target_id = targetId;
}
void Ability::set_target(sf::Vector2f* target){
	m_target = target;
}
void Ability::set_range(float range){
	m_range = range;
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////ability_ranged class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Ability_Ranged::Ability_Ranged(int myId) : Ability(myId){
	m_projectile_speed = 5*DUNIT;
	m_projectile = Projectile();
}
void Ability_Ranged::cast(int targetId){
	m_target_id = targetId;
	//m_projectile.set_position(
	//m_alive = true;
}
void Ability_Ranged::cast(sf::Vector2f* target) {
	/*deprecated method*/
}
//doesnt become alive untill the projectile is thrown
void Ability_Ranged::update(float deltaTime){
	
	//if(!m_alive)return;
	//std::cout<<"cooldown :"<<m_cool_down_current<<" \n";
	if(m_state == Ability_State::READY ){
		if(m_target_id != -1){
			if(EntityManager::instance()->in_range(m_my_id, m_target_id, m_range)){
				m_state=Ability_State::CHARGING;
			}
			else{//walk towards the target
				EntityManager::instance()->move_towards(m_my_id, m_target_id);
			}
		}
	}
	else if ( m_state == Ability_State::CHARGING){
		//play animation
		//count down for delay
		m_cast_speed_time+=deltaTime;
		if(m_cast_speed_time >= m_cast_speed_max)
			m_state = Ability_State::ACTION;
	}
	else if( m_state == Ability_State::ACTION){
		m_state = Ability_State::COOLDOWN;
		m_projectile.set_alive(true);
		m_projectile.set_targetId(m_target_id);
		m_projectile.set_position(EntityManager::instance()->getEntity(m_my_id)->getPosition());
		//m_target_id = -1;
		
	}
	else{ //cooldown state
		if( m_cool_down_current <m_cool_down_max){
			m_cool_down_current += deltaTime;
		}
		else{
			m_cool_down_current=0;
			m_target_id=-1;
			m_state = Ability_State::READY;
		}
	}
	//also update the projectile all the time and have it check if its collided, 
	//check returns true/false upon which i do damage
	if(m_projectile.update(deltaTime, m_projectile_speed)){
		EntityManager::instance()->getEntity(m_projectile.get_target_id())->take_damage(m_damage);

	}
}
void Ability_Ranged::draw(sf::RenderWindow* window){
	//soon, probably draw the projectiles or some shit 
	m_projectile.draw(window);
}
float Ability_Ranged::get_projectile_speed(){
	return m_projectile_speed;
}
////////////////////////////////////////////////////////////////////////////
/////////////////////////////ability_ranged class///////////////////////////
////////////////////////////////////////////////////////////////////////////

Ability_AOE::Ability_AOE(int myId) : Ability(myId){
	m_shape = sf::RectangleShape(sf::Vector2f(-1000, -1000));
	m_aoe_range = 20*DUNIT;
	m_damage_delay_time=0;
	m_damage_delay_max = 0.8;
}
void Ability_AOE::cast(int targetId){
	//m_target_id = targetId;
}
void Ability_AOE::cast(sf::Vector2f* target) {
	m_target = target;
}
//doesnt become alive untill the projectile is thrown
void Ability_AOE::update(float deltaTime){
	if(m_state == Ability_State::READY){
		if(EntityManager::instance()->in_range(m_my_id, m_target, m_range)){
			m_state=Ability_State::CHARGING;
		}
		else{//walk towards the target
			EntityManager::instance()->move_towards(m_my_id, m_target);
		}
	}
	else if ( m_state == Ability_State::CHARGING){
		//play animation
		//count down for delay
		m_cast_speed_time+=deltaTime;
		if(m_cast_speed_time >= m_cast_speed_max){//so play the animation player
			m_damage_delay_time+=deltaTime;
			if(m_damage_delay_time >= m_damage_delay_max){//then play the aoe spell animation
				m_state = Ability_State::ACTION;
			}
		}
	}
	else if( m_state == Ability_State::ACTION){
		m_state = Ability_State::COOLDOWN;
		//do the damage
	}
	else if(m_state == Ability_State::COOLDOWN && m_cool_down_current <m_cool_down_max){
		m_cool_down_current += deltaTime;
	}
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////projectile class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Projectile::Projectile(){
	m_velocity = sf::Vector2f(0, 0);
	m_shape = sf::CircleShape(5);
	m_shape.setFillColor(sf::Color::Red);
	m_alive = false;
}
Projectile::Projectile(sf::Vector2f vel): m_velocity(vel){
	m_shape = sf::CircleShape(5);
	m_shape.setFillColor(sf::Color::Red);
	m_alive = false;
}
void Projectile::draw(sf::RenderWindow* window){
	if(!m_alive) return;
	window->draw(m_shape);
}
bool Projectile::update(float deltaTime, float speed){
	if(!m_alive) return false;
	m_velocity = EntityManager::instance()->get_direction(m_shape.getPosition(), m_target_id);
	m_shape.setPosition(m_shape.getPosition() + m_velocity * speed);
	//distance between you and target
	 Entity* ent = EntityManager::instance()->getEntity(m_target_id);
	if(math_get_distance(m_shape.getPosition(), ent->getPosition()) < 10){
		//colided
		m_alive = false;
		return true;
	}
	return false;
}
void Projectile::set_position(sf::Vector2f pos){
	m_shape.setPosition(pos);
}
void Projectile::set_velocity(sf::Vector2f vel){
	m_velocity = vel;
}