#include "Unit.h"

Unit::Unit(int hp, int atk, UnitType type, UnitStatus status, std::string name) 
	: _hp(hp)
	, _atk(atk)
	, _type(type)
	, _status(status)
	, _name(name) 
{}

void Unit::Attach(IObserver* observer) {
	unit_list_observer_.push_back(observer);
}
void Unit::Detach(IObserver* observer) {
	unit_list_observer_.remove(observer);
}
void Unit::Notify() {
	std::list<IObserver*>::iterator iterator = unit_list_observer_.begin();
	//HowManyObserver();
	while (iterator != unit_list_observer_.end()) {
		(*iterator)->UpdateUnitChange(*this);
		++iterator;
	}
}

Unit::~Unit() {};

int Unit::getHP() const {
	return _hp;
}
int Unit::getDmg() const {
	return _atk;
}
int Unit::getType() const {
	return _type;
}
UnitStatus Unit::getStatus() const {
	return _status;
}

std::string Unit::getName() const {
	return _name;
}

void Unit::setHP(int hp) {
	_hp = hp;
	Notify();
}

void Unit::setDmg(int damage) {
	_atk = damage;
	Notify();
}

void Unit::setStatus(UnitStatus status) {
	_status = status;
	Notify();
}

void Unit::setName(std::string name) {
	Notify();
}

bool Unit::isAlive() {
	return _hp > 0 ? true : false;
}

void Unit::attack(Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards) {
	if (getDmg() != 0) // ex: brawl has 0.atk => no need to proceed attack func
	{
		if (enemy_hero.isAlive()) {
			//card attack cards of enemy
			if (enemy_onboard_cards.size() != 0) {
				for (auto& card : enemy_onboard_cards) {
					int newHP = card->getHP() - getDmg();
					(newHP >= 0) ? card->setHP(newHP) : card->setHP(0);
				}
			}

			//card attack hero of enemy
			int newHP_hero = enemy_hero.getHP() - this->getDmg();
			(newHP_hero >= 0) ? enemy_hero.setHP(newHP_hero) : enemy_hero.setHP(0);
			//std::cout << this->_name << "  attacked: " << this->getDmg() << "damage." << std::endl;
		}
	}
	else
		Notify();
}

void Unit::attack(Unit& enemy_hero) {
	if (this->getDmg() != 0) // ex: brawl has 0.atk => no need to proceed attack func
	{
		if (enemy_hero.isAlive()) {
			//card attack hero of enemy
			int newHP_hero = enemy_hero.getHP() - this->getDmg();
			(newHP_hero >= 0) ? enemy_hero.setHP(newHP_hero) : enemy_hero.setHP(0);
			//std::cout << this->_name << "  attacked: " << this->getDmg() << "damage." << std::endl;
		}
	}
	else
		Notify();
}

std::string Unit::typeToText() {
	std::string hero = "HERO";
	std::string minion = "MINION";
	std::string shaman = "SHAMAN";
	std::string destroyer = "DESTROYER";
	std::string unknown = "UNKNOWN";
	std::string text = "";
	switch (_type) {
	case UnitType::HERO:
	{
		text = hero;
		break;
	}
	case UnitType::MINION:
	{
		text = minion;
		break;
	}
	case UnitType::SHAMAN:
	{
		text = shaman;
		break;
	}
	case UnitType::DESTROYER:
	{
		text = destroyer;
		break;
	}
	case UnitType::UNKNOWN:
	{
		text = unknown;
		break;
	}
	default:
		break;
	}
	return text;
}

void Unit::spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards) {}
