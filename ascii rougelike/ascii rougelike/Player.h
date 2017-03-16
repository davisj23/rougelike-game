#pragma once

class Player
{
	public();
	void init(int level, int health, int attack, int defense, int experience);

	//setters
	void setPosition(int x, int y);

	//Getters
	void getposition(int &x, int &y);

private:
	//Properties
	int _level;
	int _health:
	int _attack;
	int _defence;
	int _experience;

	//Position
	int _x;
	int _y;
	
};