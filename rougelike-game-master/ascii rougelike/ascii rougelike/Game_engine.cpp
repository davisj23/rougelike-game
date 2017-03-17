#include "Game_engine.h"
#include <iostream>
#include <conio.h>


//sets up the game. also has the hero starting stats
game_engine::game_engine(string levelFileName){

	_hero.init(1, 100, 10, 10, 0);

	_engine.load(levelFileName, _hero);

	system("PAUSE");
}

void game_engine::start_game() {

	bool isDone = false;

	while (isDone != true) {
		_engine.print();
		hero_move();
		_engine.updateMonsters(_hero);

	}

}


void game_engine::hero_move() {
	char input;
	printf("Enter a move command (w/s/a/d):");
	input = _getch();

	_engine.hero_move(input, _hero);


}