#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>

#include "Game_engine.h" // source not found? solved was useing <> instead of "" was stuck on that for so long that i took an hour break from this

using namespace std;
// when the program is started this loads up the map starts the game.
int main()
{
	game_engine gameSystem("level1.txt"); // can change this to change map

	gameSystem.start_game();


	return 0;
}