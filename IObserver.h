#pragma once
#pragma once
class Player;
class Unit;
//#include "Player.h"
class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update(const Player& players) = 0;
	virtual void UpdateUnitChange(const Unit& units) = 0;
	//virtual IObserver* Clone();
};

