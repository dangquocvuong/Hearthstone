#pragma once
#include "Unit.h"
#include "SystemDefined.h"

class Shaman :public Unit {
public:
	Shaman(int _hp, int _atk, std::string _name);

	Shaman(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name);

	void spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards);

	~Shaman();
};