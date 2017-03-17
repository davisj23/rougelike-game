#include "Hero.h"
#include <random>
#include <ctime>
using namespace std;

//sets the starting position of the hero to zero
Hero::Hero() {
	_x = 0;
	_y = 0;
}

//Initializes the hero with his stats
void Hero::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_health_points = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

//rng attack.
int Hero::attack() {
	static default_random_engine random_number_engine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(random_number_engine);

}
//sets the postion of the player
void Hero::set_location(int x, int y) {
	_x = x;
	_y = y;
}

//when the hero levels up it will reset his xp and give him a bunch of stat increases.
void Hero::addExperience(int experience){
	_experience += experience;

	//level up
	while (_experience > 50) {
		printf("Leveled up!\n");
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health_points += 10;
		_level++;
		system("PAUSE");

	}

}


//find the location of the hero
void Hero::find_location(int &x, int &y) {
	x = _x;
	y = _y;
}
// this will take the damage the hero gets and apply defence. it will then see if their is any leftover damage. see if hero is dead. and then returnto see if he is dead
int Hero::take_damage(int attack) {
	attack -= _defense;
	//check if the attack does damage. if it does then it will take the left over damage and take that away from the heros health
	if (attack > 0) {
		_health_points -= attack;
		//check if hero died due to the attck will tell game he is dead. which will case the game to close
		if (_health_points <= 0) {
			return 1;
		}
	}
	else {
		return 0;
	}
	return 0;
}