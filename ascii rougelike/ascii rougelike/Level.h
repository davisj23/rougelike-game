#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level
{
public:
	Level();

	void load(string fileName, Player &player);
	void print();

	void movePlayer(char input, Player &player);
	//Getters
	char getTile(int x, int y);
	//Setters
	void setTile(int x, int y, char tile);

private:
	void processPlayerMove(Player &player, int targetX, int targetY);
	void battleMoster(Player &player, int targetX, int targetY);
private:
	vector <string> _levelData;
	vector <Enemy> _enemies;
};
