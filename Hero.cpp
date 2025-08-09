#include "Hero.h"

Hero::Hero(int hp, int atk, UnitType type, UnitStatus status, std::string name)
	: Unit::Unit(hp, atk, type, status, name)
{
}

Hero::Hero(int hp, int atk, std::string name)
	: Hero::Hero(hp, atk, UnitType::HERO, UnitStatus::INACTIVE, name)
{
}

Hero::~Hero() 
{
}