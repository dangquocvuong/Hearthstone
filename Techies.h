#pragma once
#include "Unit.h"
#include "SystemDefined.h"

class Techies :public Unit {
public:
	Techies(int _hp, int _atk, std::string _name);

	Techies(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name);

	~Techies();
};


