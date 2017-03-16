#include "GameSystem.h"


//Constructor sets up the game
GameSystem::GameSystem(string levelFileName){

	_level.load(levelFileName);
	_level.print();

	system("PAUSE");

}

void GameSystem::playGame() {

}