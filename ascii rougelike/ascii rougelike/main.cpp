#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>

#include "GameSystem.h" // source not found? solved was useing <> instead of "" was stuck on that for so long that i took an hour break from this

using namespace std;

int main()
{
	GameSystem gameSystem("level1.txt");

	gameSystem.playGame();


	return 0;
}