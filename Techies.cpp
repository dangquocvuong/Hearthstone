#include "Techies.h"

Techies::Techies(int _hp, int _atk, std::string _name)
	: Unit::Unit(_hp, _atk, UnitType::MINION, UnitStatus::INACTIVE, _name)
{
}

Techies::Techies(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name)
	: Unit::Unit(_hp, _atk, _type, _status, _name)
{
}

Techies::~Techies() {}