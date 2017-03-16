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
				_enemies.push_back(Enemy("Snake", tile, 1, 1, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //snake
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 20, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 50000000));
				_enemies.back().setPosition(j, i);
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
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

void Level::updateEnemies(Player &player) {
	char aiMove;
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);

		switch (aiMove) {

		case 'w':// up
			processPlayerMove(player, playerX, playerY - 1);
			break;
		case 's':// down
			processPlayerMove(player, playerX, playerY + 1);
			break;
		case 'a'://left
			processPlayerMove(player, playerX - 1, playerY);
			break;
		case 'd'://right
			processPlayerMove(player, playerX + 1, playerY);
			break;

		}

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

void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {

	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);

	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case'.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '#':
		break;
	default:
		break;
	}

}

void Level::battleMoster(Player &player, int targetX, int targetY) {

	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	string enemeyName;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {

		_enemies[i].getPosition(enemyX, enemyY);
		enemeyName = _enemies[i].getName();

		if (targetX == enemyX && targetY == enemyY){

			//Fight
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of %d\n", enemeyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("Monster died!\n");

				//remove enemies
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

					system("PAUSE");
				player.addExperience(attackResult);

				return;

			}
			//Monster trun! if the Monster survies this will roll the monsters trun so it can deal damage to the player
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of %d\n", enemeyName.c_str(), attackRoll);
			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(playerX, playerY, 'X');
				print();
				printf("You died!\n");
				system("PAUSE");

				exit(0);
			}
			system("PAUSE");
			return;

		}
	}
	
}