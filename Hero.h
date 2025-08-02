#pragma once
#include "Unit.h"
#include "SystemDefined.h"
//class Unit;
class Hero : public Unit {
public:
	Hero() : Hero::Hero(0, 0, UnitType::HERO, UnitStatus::INACTIVE, "Unknown") {}

	Hero(int hp, int atk, std::string name) :\
		Hero::Hero(hp, atk, UnitType::HERO, UnitStatus::INACTIVE, name) {}

	Hero(int hp, int atk, UnitType type, UnitStatus status, std::string name) :\
		Unit::Unit(hp, atk, type, status, name) {}

	~Hero() {};
};
