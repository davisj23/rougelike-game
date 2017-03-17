#include "Monster.h"
#include <random>
#include <ctime>

//sets up the veriables
Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp) {
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = xp;




}

//sets the location of the enemy
void Enemy::set_local(int x, int y) {
	_x = x;
	_y = y;
}

//find the location of the enemy
void Enemy::get_local(int &x, int &y) {
	x = _x;
	y = _y;
}

//rng for the monsters attack
int Enemy::attack() {
	static default_random_engine random_num_engine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(random_num_engine);

}
// calculates how much damage the monster will take. also checks to see if it is dead
int Enemy::takeDamage(int attack) {
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		//check if he died. if the monster dies then the player will get some xp to help him level up
		if (_health <= 0) {
			return _experienceValue;
		}
	}
	else {
		return 0;
	}
	return 0;
}
//A.I that controls the monster
char Enemy::get_ai_move(int playerX, int playerY) {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);

	int distance;
	int dx = _x - playerX; //diffrence in x
	int dy = _y - playerY; //diffrence in y
	int adx = abs(dx); //absolute value dx
	int ady = abs(dy); // absolute value dy


	distance = adx + ady;


	/* this piece of code will get the monster to chase the player if they are within 5 tiles of the monster.
	first the above calculation will determin how far the player is from each monster every turn. if they are less than 5 the monster will follow then.
	it does this by determening wich side the player is farthest from them in. then it will move towards the player down the axies it is fauther away from the player on.
	this means it will take the shortest route to the player. problem is that it wont recongnise walls so it will keep walking into a wall if the player is on the oother side of it*/
	if (distance <= 5) {
		//Move along X axis
		if (adx > ady) {
			if (dx > 0) {
				return 'a';
			}
			else {
				return 'd';
			}
		} else { // Move along Y axis
			if (dy > 0) {
				return 'w';
			}
			else {
				return 's';
			}
		}


	}
	// if player if more then 5 away the monster will walk in a random direction or do nothing
	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 's';
	case 2:
		return 'w';
	case 3:
		return 'd';
	default:
		return '.';

	}
}
