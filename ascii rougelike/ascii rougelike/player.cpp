#include "Player.h"

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
	_defence = defense;
	_experience = experience;
}

//sets the postion of the player
void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

//find the position of the payer
void Player::getposition(int &x, int &y) {
	x = _x;
	y = _y;
}