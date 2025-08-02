#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "SystemDefined.h"
#include "ISubject.h"
#include "IObserver.h"

class Unit : public ISubject {
	int _hp;
	int _atk;
	UnitType _type;
	UnitStatus _status;
	std::string _name;

	std::list<IObserver*> unit_list_observer_;
public:
	virtual ~Unit() {};
	Unit() : _hp(0), _atk(0), _type(UnitType::UNKNOWN), _status(UnitStatus::INACTIVE), _name("Unit") {}
	Unit(int hp, int atk, UnitType type, UnitStatus status, std::string name) :\
		_hp(hp), _atk(atk), _type(type), _status(status), _name(name) {}

	void Attach(IObserver* observer) override {
		unit_list_observer_.push_back(observer);
	}
	void Detach(IObserver* observer) override {
		unit_list_observer_.remove(observer);
	}
	void Notify() override {
		std::list<IObserver*>::iterator iterator = unit_list_observer_.begin();
		//HowManyObserver();
		while (iterator != unit_list_observer_.end()) {
			(*iterator)->UpdateUnitChange(*this);
			++iterator;
		}
	}

	//virtual Unit* Clone() {
	//	//std::cout << "Unit clone" << std::endl;
	//	return new Unit(_hp,_atk,_type,_status,_name);
	//}

	int getHP()   const {
		return _hp;
	}
	int getDmg()  const {
		return _atk;
	}
	int getType() const {
		return _type;
	}
	UnitStatus getStatus() const {
		return _status;
	}

	virtual  std::string getName() const {
		return _name;
	}

	virtual  void setHP(int hp = 999) {
		_hp = hp;
		Notify();
	}
	virtual  void setDmg(int damage = 999) {
		_atk = damage;
		Notify();
	}
	virtual void setStatus(UnitStatus status = UnitStatus::INACTIVE) {
		_status = status;
		Notify();
	}
	virtual void setName(std::string name) {
		Notify();
	}
	virtual bool isAlive() {
		return _hp > 0 ? true : false;
	}

	virtual void attack(Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards) {
		if (this->getDmg() != 0) // ex: brawl has 0.atk => no need to proceed attack func
		{
			if (enemy_hero.isAlive()) {
				//card attack cards of enemy
				if (enemy_onboard_cards.size() != 0) {
					for (auto& card : enemy_onboard_cards) {
						int newHP = card->getHP() - this->getDmg();
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
	
	virtual void attack(Unit& enemy_hero) {
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

	std::string typeToText() {
		std::string hero = "HERO";
		std::string minion = "MINION";
		std::string shaman = "SHAMAN";
		std::string destroyer = "DESTROYER";
		std::string unknown = "UNKNOWN";
		std::string text = "";
		switch (this->_type) {
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

	virtual void spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards) {}
	//virtual std::list<IObserver*> getListObserver() {
	//	return unit_list_observer_;
	//}
};
