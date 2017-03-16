#include "Player.h"
#include <random>
#include <ctime>
using namespace std;

//Constructor sets first position to zero at game start
Player::Player() {
	_x = 0;
	_y = 0;
}

//Initializes the player with properties
void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}
int Player::attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);

}
//sets the postion of the player
void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::addExperience(int experience){
	_experience += experience;

	//level up
	while (_experience > 50) {
		printf("Leveled up!\n");
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health += 10;
		_level++;
		system("PAUSE");

	}

}


//find the position of the payer
void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Player::takeDamage(int attack) {
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		//check if he died
		if (_health <= 0) {
			return 1;
		}
	}
	else {
		return 0;
	}
	return 0;
}