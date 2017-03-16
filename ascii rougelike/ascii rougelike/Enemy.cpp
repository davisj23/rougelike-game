#include "Enemy.h"
#include <random>
#include <ctime>


Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp) {
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = xp;




}

//sets the postion of the enemy
void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

//find the position of the enemy
void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Enemy::attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);

}

int Enemy::takeDamage(int attack) {
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		//check if he died
		if (_health <= 0) {
			return _experienceValue;
		}
	}
	else {
		return 0;
	}
	return 0;
}

char Enemy::getMove(int playerX, int playerY) {

	int distance;
	int dx; //diffrence in x
	int dy; //diffrence in y



	distance = abs(_x - playerX) + abs(_y - playerY);

	if (distance <= 5) {


	}

}
