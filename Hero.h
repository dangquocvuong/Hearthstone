#pragma once
#include "Unit.h"
#include "SystemDefined.h"
//class Unit;
class Hero : public Unit {
public:
	Hero(int hp, int atk, std::string name);
	Hero(int hp, int atk, UnitType type, UnitStatus status, std::string name);
	~Hero();
};
