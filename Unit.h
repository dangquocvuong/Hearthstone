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
	virtual ~Unit();
	Unit(int hp, int atk, UnitType type, UnitStatus status, std::string name);

	void Attach(IObserver* observer) override;
	void Detach(IObserver* observer) override;
	void Notify() override;

	int getHP()   const;
	int getDmg()  const;
	int getType() const;

	virtual  std::string getName() const;

	virtual void setHP(int hp = 999);
	virtual void setDmg(int damage = 999);
	virtual void setStatus(UnitStatus status = UnitStatus::INACTIVE);
	virtual void setName(std::string name);
	virtual bool isAlive();
	virtual void attack(Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards);
	virtual void attack(Unit& enemy_hero);
	virtual void spell(Unit& active_hero, Unit& enemy_hero, std::vector<Unit*>& enemy_onboard_cards, std::vector<Unit*>& alliance_onboard_cards);

	std::string typeToText();
	UnitStatus getStatus() const;
};
