#pragma once
#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);
	
	//sets 
	void set_local(int x, int y);

	//Gets
	void get_local(int &x, int &y);
	string getName() { return _name; }
	char getTile() { return _tile; }
	int attack();
	int takeDamage(int attack);

	// Gets AI move command
	char get_ai_move(int playerX, int playerY);

private:
	//because their is more than one monster unlike the hero they will need names to differaciate themsleves n their class
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;
	
	int _x;
	int _y;


};

