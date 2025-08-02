//#pragma once
#include <iostream>
#include "Creator.h"
#include "Player.h"
#include "GameMananger.h"

using namespace std;

int main()
{
	//cout << "blalalal";
	GameMananger mananger;
	mananger.initializeNewGame();
	mananger.startGame();
	mananger.endGame();
	return 0;
}
