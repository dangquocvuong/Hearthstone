#include "Destroyer.h"

Destroyer::Destroyer(int _hp, int _atk, std::string _name)
	: Unit::Unit(_hp, _atk, UnitType::DESTROYER, UnitStatus::INACTIVE, _name)
{
}

Destroyer::Destroyer(int _hp, int _atk, UnitType _type, UnitStatus _status, std::string _name)
	: Unit::Unit(_hp, _atk, _type, _status, _name)
{
}

void Destroyer::spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards) {
	//delete random minion
	int count = 0;
	if (enemy_onboard_cards.size() != 0) {
		srand(static_cast<int>(time(NULL)));
		int x = rand() % enemy_onboard_cards.size();
		//std::cout << "x=" << x << ", enemy_onboard_cards.size()= " << enemy_onboard_cards.size() << std::endl;
		for (auto& i : enemy_onboard_cards) {
			if (i->getType() == UnitType::MINION) {
				count++;
			}
		}
		if (count != 0) {
			int temp = 50;
			while (temp > 0) {
				if (enemy_onboard_cards.at(x)->getType() == UnitType::MINION) {
					enemy_onboard_cards.at(x)->setHP(0);
					break;
				}
				temp--;
			}
		}
	}
}

Destroyer::~Destroyer()
{
}

