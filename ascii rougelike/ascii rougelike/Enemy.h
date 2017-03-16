#pragma once
#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);
	
	//setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);
	string getName() { return _name; }

	int attack();
	int takeDamage(int attack);

	// Gets AI move command
	char getMove(int playerX, int playerY);

private:
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;
	// add in attack range for AI

	/*vector <Items> possibleDrops
	this is extra code that i plan to add in a bit. will contain a list of items that monsters could drop
	can also use flote point to set the percentage*/

	//Position
	int _x;
	int _y;


};

