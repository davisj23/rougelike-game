#pragma once

class Hero
{
public:()
	Hero();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();

	int Hero::take_damage(int attack);

	//sets
	void set_location(int x, int y);

	void addExperience(int experience);

	// gets
	void find_location(int &x, int &y);


private:
	//stats of the hero. these dont need to be seen as i dont what these to accidently be altered later down the code by accident
	int _level;
	int _health_points;
	int _attack;
	int _defense;
	int _experience;

	//same reason as the stats
	int _x;
	int _y;
	
};