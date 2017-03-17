#pragma once
#include "Hero.h"
#include "Engine.h"
#include <string>
using namespace std;

//hero and engine are private because their core files dont need to be edited join play
class game_engine
{
public:
	game_engine(string levelFileName);

	void start_game();
	void hero_move();
private:
	Engine _engine;
	Hero _hero;
};