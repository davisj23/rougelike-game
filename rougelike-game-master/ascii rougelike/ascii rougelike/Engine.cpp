#include <fstream>
#include "Engine.h"
#include <iostream>
#include <cstdio>
using namespace std;
//bulk of the code and processing is done here but i have also tryed to spreed it out in the other files
Engine::Engine() {

}

void Engine::load(string fileName, Hero &hero) {

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
		_engine_data.push_back(line);
	}

	file.close();

	//process the level
	char tile;
	for (int i = 0; i < _engine_data.size(); i++) {
		for (int j = 0; j < _engine_data[i].size(); j++) {
			tile = _engine_data[i][j];
			/* this piece bellow tells us what the diffrent symbols represent in game assigens them to a class. in this case player/hero or monster.
			it also has their stats and names . should be easyer to balance numbers cuz of this*/
			switch (tile) {
			case '@' : // this is the hero. the player will be playeing as this. he must defeat the monsters to win. ps. cant win drag too op.
				hero.set_location(j,i);
				break;
			case 'R': //a ratman
				_monsters.push_back(Enemy("Ratman", tile, 1, 1, 1, 10, 50));
				_monsters.back().set_local(j, i);
				break;
			case 'K': // a ork
				_monsters.push_back(Enemy("Ork", tile, 2, 10, 5, 35, 150));
				_monsters.back().set_local(j, i);
				break;
			case 'O': //a ogloid
				_monsters.push_back(Enemy("Ogloid", tile, 4, 20, 20, 200, 500));
				_monsters.back().set_local(j, i);
				break;
			case 'D': // a drake
				_monsters.push_back(Enemy("Drak", tile, 100, 2000, 2000, 2000, 50000000));
				_monsters.back().set_local(j, i);
				break;
			case 'B': // a Theif
				_monsters.push_back(Enemy("Theif", tile, 3, 15, 10, 100, 250));
				_monsters.back().set_local(j, i);
			}
			}
		}
	}

//refreshes the screen
void Engine::print() {

	cout << string(100, '\n');
	for (int i = 0; i < _engine_data.size(); i++) {
		printf("%s\n", _engine_data[i].c_str());

	}
	printf("\n");
}

// this allows the hero to move. it waits for a preset key to be input and will then run the move command. will also tell you if u pressed the wrong key
void Engine::hero_move(char input, Hero &player) {


	int heroX;
	int heroY;
	player.find_location(heroX, heroY);

	char moveTile;

	switch (input) {

	case 'w':// up
	case 'W':
		process_move_hero(player, heroX, heroY - 1);
		break;
	case 's':// down
	case 'S':
		process_move_hero(player, heroX, heroY + 1);
		break;
	case 'a'://left
	case 'A':
		process_move_hero(player, heroX - 1, heroY);
		break;
	case 'd'://right
	case 'D':
		process_move_hero(player, heroX + 1, heroY);		
		break;
	
	default:
		
		printf("INVALID INPUT! \n");
		system("PAUSE");
		break;

	}


}

/*if the A.I sents and move command or the monster randonly rolls on a move number then this piece of code will get the monster to move.
now doent move the playe instead of monsters.
now doent tp monsters to player location*/
void Engine::updateMonsters(Hero &player) {
	char aiMove;
	int heroX;
	int heroY;
	int monsterX;
	int monsterY;

	player.find_location(heroX, heroY);

	for (int i = 0; i < _monsters.size(); i++) {
		aiMove = _monsters[i].get_ai_move(heroX, heroY);
		_monsters[i].get_local(monsterX, monsterY);

		switch (aiMove) {

		case 'w':// up
			process_move_monster(player, i, monsterX, monsterY - 1);
			break;
		case 's':// down
			process_move_monster(player, i, monsterX, monsterY + 1);
			break;
		case 'a'://left
			process_move_monster(player, i, monsterX - 1, monsterY);
			break;
		case 'd'://right
			process_move_monster(player, i, monsterX + 1, monsterY);
			break;

		}

	}

}




char Engine::getTile(int x, int y) {
	return _engine_data[y][x];
}

void Engine::setTile(int x, int y, char tile) {
	_engine_data[y][x] = tile;

}

/*every time the player moves this will decide what will happen. for example if the player moves into a open air space the game will just mark the new pplayer location with an
@ and put  . in the players last location. will also block player from walling though walls and will battle monsters if the hero and monsters collide*/
void Engine::process_move_hero(Hero &player, int targetX, int targetY) {
	int heroX;
	int heroY;
	player.find_location(heroX, heroY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) { 
	case'.':
		player.set_location(targetX, targetY);
		setTile(heroX, heroY, '.');// changes players pervious position to a .
		setTile(targetX, targetY, '@');// sets players new position to a @
		break;
	case '#':
		break;
	default:
		fight_monster(player, targetX, targetY);
		break;
	}
}

/*same as the above but this one is for monsters. no reason to go in to detail as i just copy pasted the above here and changed a few things. but this will allow monsters to start fights with the hero*/
void Engine::process_move_monster(Hero &player, int enemyIndex, int targetX, int targetY) {

	int heroX;
	int heroY;
	int monsterX;
	int monsterY;

	_monsters[enemyIndex].get_local(monsterX, monsterY);

	player.find_location(heroX, heroY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case'.':
		_monsters[enemyIndex].set_local(targetX, targetY);
		setTile(monsterX, monsterY, '.');
		setTile(targetX, targetY, _monsters[enemyIndex].getTile());
		break;
	case '@' :
		fight_monster(player, monsterX, monsterY);
		break;
	default:
		break;
	}

}

/*this is for fights. what this will do is when it is activated it will locate the player and find out what monster has collided with him
the game will then roll for the heros attack and see if it kills the monster. if it does the fight ends if it doesnt the monster will role.
then the next turn starts and this will rerun if the hero decides to keep in fighting. hero can also run away as they get to move first in a turn.
but monsters will chase as they move the same distance per turn as the player. if monster dies player will alsos get exp. 
one last note. monsters move in turns aswell. this means that multiple monster should be able to fight a single hero in a single turn as long as their is space. can also make some tweaks to allow monster
to fight each other.*/
void Engine::fight_monster(Hero &player, int targetX, int targetY) {

	int monsterX;
	int monsterY;
	int heroX;
	int heroY;
	int attackRoll;
	int attackResult;
	string monster_name;

	player.find_location(heroX, heroY);

	for (int i = 0; i < _monsters.size(); i++) {

		_monsters[i].get_local(monsterX, monsterY);
		monster_name = _monsters[i].getName();

		if (targetX == monsterX && targetY == monsterY){

			//Fight
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of %d\n", monster_name.c_str(), attackRoll);
			attackResult = _monsters[i].takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("Monster died!\n");

				//remove enemies
				_monsters[i] = _monsters.back();
				_monsters.pop_back();
				i--;

					system("PAUSE");
				player.addExperience(attackResult);

				return;

			}
			//Monster trun! if the Monster survies this will roll the monsters trun so it can deal damage to the player
			attackRoll = _monsters[i].attack();
			printf("%s attacked player with a roll of %d\n", monster_name.c_str(), attackRoll);
			attackResult = player.take_damage(attackRoll);

			if (attackResult != 0) {
				setTile(heroX, heroY, 'X');
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