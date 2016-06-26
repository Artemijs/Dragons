#include "Ability.h"
#include "Macros.h"
#include "EntityManager.h"
#include "Math.h"
#include "Level.h"
#include "CollisionManager.h"
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

////////////////////////////////////////////////////////////////////////////
/////////////////////////////Movement class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Ability_Movement::Ability_Movement(int myid): Ability(myid){
	m_alive = false;
	m_damage = 0;
	m_cast_speed_max = 0.1;//third of a second
	m_cast_speed_time=0;
	m_mana_cost = 0;
	m_cool_down_max = 0;
	m_cool_down_current = 0;
	m_range = 1;
	m_target_id = -1;
	m_target = 0;
	m_state = Ability_State::READY;
}
Ability_Movement::~Ability_Movement(){
	
}
void Ability_Movement::cast(int targetId){
	if(m_state != Ability_State::READY) return;
	//get the target id of the tile 
	//use range as number of tiles to move
	int range = m_range;
	//get current tile
	Tile* n = Level::instance()->
		get_tile(EntityManager::instance()->getEntity(m_my_id)->get_tile());
	while(range!=0){
		Tile* t = n->get_neighbor(TILE_NEIGHBORS(targetId));
		if(t == 0) break; // stop looping if reached edge of map
		n = t;
		range--;
	}
	if(n == 0) return;
	m_target_id = n->get_id();
	
}
void Ability_Movement::cast(sf::Vector2f* target){

}
void Ability_Movement::update(float deltaTime){
	//std::cout<<"state "<<m_state<<" "<<m_target_id<<"\n";
	//std::cout<<"cooldown :"<<m_cool_down_current<<" \n";
	if(m_state == Ability_State::READY ){
		if(m_target_id != -1){
			//this is where you would turn to target
			m_state=Ability_State::CHARGING;
		}
	}
	if ( m_state == Ability_State::CHARGING){
		m_cast_speed_time+=deltaTime;
		if(m_cast_speed_time >= m_cast_speed_max){
			m_state = Ability_State::ACTION;
			m_cast_speed_time=0;
		}
	}
	if( m_state == Ability_State::ACTION){
		bool action_finished = action();
		if(action_finished){
			m_state = Ability_State::COOLDOWN;
			Entity* ent = EntityManager::instance()->getEntity(m_my_id);
			ent->set_tile(m_target_id);
			ent->set_state(EntityState::IDLE);
			m_target_id = -1;
		}
	}
	if( m_state == Ability_State::COOLDOWN){ //cooldown state
		if( m_cool_down_current <m_cool_down_max){
			m_cool_down_current += deltaTime;
		}
		else{
			m_cool_down_current=0;
			m_target_id=-1;
			m_state = Ability_State::READY;
			m_already_hit_ents.clear();
			
		}
	}
}
void Ability_Movement::draw(sf::RenderWindow* window){

}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////STEP class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Ability_Step::Ability_Step(int myid): Ability_Movement(myid){

}
Ability_Step::~Ability_Step(){
}
bool Ability_Step::action(){
	bool over= false;
	Entity* me = EntityManager::instance()->getEntity(m_my_id);
	Tile* tile = Level::instance()->get_tile(m_target_id);
	float move_spid = me->get_stats()->get_stat(Stat_Type::MOVE_SPEED);
	sf::Vector2f vel =
		math_get_direction(me->getPosition()+me->get_HeightWidth(), tile->get_centre())* move_spid;
	me->move_hard(vel);
	float dist = math_get_distance(me->getPosition()+me->get_HeightWidth(), tile->get_centre());
	//std::cout<<dist<<"  "<<vel.x<<" "<<vel.y<<"\n";
	return (dist <2.3);
}


////////////////////////////////////////////////////////////////////////////
/////////////////////////////BLINK class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Ability_Blink::Ability_Blink(int myid): Ability_Movement(myid){
	m_alive = false;
	m_damage = 0;
	m_cast_speed_max = 0.1;//third of a second
	m_cast_speed_time=0;
	m_mana_cost = 0;
	m_cool_down_max = 1;
	m_cool_down_current = 0;
	m_range = 1;
	m_target_id = -1;
	m_target = 0;
	m_state = Ability_State::READY;
}
Ability_Blink::~Ability_Blink(){
}
bool Ability_Blink::action(){
	//teleport the player to the target instantly 
	bool over= false;
	Entity* me = EntityManager::instance()->getEntity(m_my_id);
	Tile* tile = Level::instance()->get_tile(m_target_id);
	me->setPosition(tile->get_centre() - me->get_HeightWidth());
	return true;
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////Strike class///////////////////////////
////////////////////////////////////////////////////////////////////////////
Ability_Lance::Ability_Lance(int myid): Ability_Movement(myid){
	m_alive = false;
	m_damage = 100;
	m_cast_speed_max = 0.1;//third of a second
	m_cast_speed_time=0;
	m_mana_cost = 0;
	m_cool_down_max = 1;
	m_cool_down_current = 0;
	m_range = 2;
	m_target_id = -1;
	m_target = 0;
	m_state = Ability_State::READY;
}
Ability_Lance::~Ability_Lance(){
}
bool Ability_Lance::action(){
	//move towards taget and damage anything you contact with
	Entity* me = EntityManager::instance()->getEntity(m_my_id);
	Tile* tile = Level::instance()->get_tile(m_target_id);
	float move_spid = me->get_stats()->get_stat(Stat_Type::MOVE_SPEED);
	sf::Vector2f vel =
		math_get_direction(me->getPosition()+me->get_HeightWidth(), tile->get_centre())* move_spid;
	me->move_hard(vel);
	float dist = math_get_distance(me->getPosition()+me->get_HeightWidth(), tile->get_centre());
	//std::cout<<dist<<"  "<<vel.x<<" "<<vel.y<<"\n";
	Entity* ent = CollisionManager::instance()->check_collision_ents(me);
	if(ent!= 0){
		bool hit = false;
		for(int i = 0; i < m_already_hit_ents.size(); ++i){
			if(m_already_hit_ents[i] == ent->get_id()){
				//already dealt damage to that entity
				hit = true;
			}
		}
		if(!hit){//do damage and remember this entity
			ent->take_damage(m_damage);
			m_already_hit_ents.push_back(ent->get_id());
			std::cout<<"collided with \n";
		}
	}
	return (dist <2.3);
}
