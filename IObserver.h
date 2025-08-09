#pragma once
class Player;
class Unit;

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update(const Player& players) = 0;
	virtual void UpdateUnitChange(const Unit& units) = 0;
};

