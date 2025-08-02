#pragma once
#include "Unit.h"
#include "SystemDefined.h"

class Shaman :public Unit {
public:
	Shaman() : Shaman::Shaman(0, 0, UnitType::SHAMAN, UnitStatus::INACTIVE, "Unknown") {}

	Shaman(int _hp, int _atk, std::string _name) :\
		Unit::Unit(_hp, _atk, UnitType::SHAMAN, UnitStatus::INACTIVE, _name) {}

	Shaman(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name) :\
		Unit::Unit(_hp, _atk, _type, _status, _name) {}

	void spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards) override {
		if (enemy_hero.isAlive()) {
			if (alliance_onboard_cards.size() != 0) {
				for (int i = 0; i < alliance_onboard_cards.size(); i++) {
					if (alliance_onboard_cards.at(i)->getType() == UnitType::MINION) {
						int current_damage = alliance_onboard_cards.at(i)->getDmg();
						alliance_onboard_cards.at(i)->setDmg(++current_damage);
					}
				}
			}
		}
	}

	~Shaman() {}
};

