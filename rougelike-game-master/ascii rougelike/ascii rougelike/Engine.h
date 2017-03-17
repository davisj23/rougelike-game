#pragma once
#include <vector>
#include <string>
#include "Hero.h"
#include "Monster.h"

using namespace std;

class Engine
{
public:
	Engine();

	void load(string fileName, Hero &player);
	void print();

	void hero_move(char input, Hero &player);
	void updateMonsters(Hero &player);

	//Gets
	char getTile(int x, int y);
	//Sets
	void setTile(int x, int y, char tile);

private:
	void process_move_hero(Hero &player, int targetX, int targetY);
	void process_move_monster(Hero &player, int enemyIndex, int targetX, int targetY);
	void fight_monster(Hero &player, int targetX, int targetY);
private:
	vector <string> _engine_data;
	vector <Enemy> _monsters;
};
