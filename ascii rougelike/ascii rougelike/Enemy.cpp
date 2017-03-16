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
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);

	int distance;
	int dx = _x - playerX; //diffrence in x
	int dy = _y - playerY; //diffrence in y
	int adx = abs(dx); //absolute value dx
	int ady = abs(dy); // absolute value dy


	distance = adx + ady;

	if (distance <= 5) {
		//Move along X
		if (adx < ady) {
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
