#include "Minion.h"

Minion::Minion(int _hp, int _atk, std::string _name)
	: Unit::Unit(_hp, _atk, UnitType::MINION, UnitStatus::INACTIVE, _name) 
{}

Minion::Minion(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name)
	: Unit::Unit(_hp, _atk, _type, _status, _name) 
{}

void Minion::spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards) {
	std::string techies = "Techies";

	if (this->getName() == "Techies" && this->isAlive() == false) {
		int active_hero_new_hp = (active_hero.getHP() - 3);
		int enemy_hero_new_hp = (enemy_hero.getHP() - 3);
		active_hero.setHP(active_hero_new_hp);
		enemy_hero.setHP(enemy_hero_new_hp);
	}
}

Minion::~Minion()
{
}