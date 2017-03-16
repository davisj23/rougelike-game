#pragma once
#include <vector>
#include <string>

using namespace std;

class Level
{
public:
	Level();

	void load(string fileName);
	void print();

private:
	vector <string> _levelData;
};

