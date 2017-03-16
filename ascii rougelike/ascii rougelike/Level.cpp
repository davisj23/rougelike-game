#include <fstream>
#include "Level.h"
#include <iostream>
#include <cstdio>
using namespace std;
Level::Level() {

}

void Level::load(string fileName, Player &player) {

	//loads the level

	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	//process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@' : // player
				player.setPosition(j,i);
				break;
			case 'S': //snake
				_enemies.push_back(Enemy("Snake", tile, 1, 1, 1, 10, 10));
				break;
			case 'g':
				_enemies.push_back(Enemy("goblin", tile, 2, 10, 5, 35, 50));
				break;
			case 'O': //snake
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 20, 200, 500));
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 50000000));
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
			}
			}
		}
	}


void Level::print() {

	cout << string(100, '\n');
	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());

	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player) {


	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile;

	switch (input) {

	case 'w':// up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':// down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a'://left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd'://right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);		
		break;
	
	default:
		
		printf("INVALID INPUT! \n");
		system("PAUSE");
		break;

	}


}

char Level::getTile(int x, int y) {
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;

}
void Level::processPlayerMove(Player &player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) { 
	case'.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');// changes players pervious position to a .
		setTile(targetX, targetY, '@');// sets players new position to a @
		break;
	case '#':
		break;
	default:
		battleMoster(player, targetX, targetY);
		break;
	}
}
void Level::battleMoster(Player &player, int targetX, int targetY) {

	int enemyX;
	int enemyY;
	int attackRoll;
	int attackResult;

	for (int i = 0; i < _enemies.size(); i++) {

		_enemies[i].getPosition(enemyX, enemyY);

		if (targetX == enemyX && targetY == enemyY){

			//Fight
			attackRoll = player.attack();
			printf("Player attacked moster with a roll of %d", attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {
				printf("Monster died!\n");
					system("PAUSE");
				player.addExperience(attackResult);

				setTile(targetX, targetY, '.');
				return;

			}
			//Monster trun



			return;

		}
	}
	
}