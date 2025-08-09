#pragma once
#include "Unit.h"
#include "Hero.h"
#include "Minion.h"
#include "Shaman.h"
#include "Destroyer.h"

class Creator {
public:
	virtual ~Creator() {}
	virtual Unit* create() const = 0;
};

class CreateDestroyer_Brawl : public Creator {
public:
	inline Unit* create() const override {
		return new Destroyer(0, 0, std::string("Brawl  "));
	}
};

class CreateHero_Slark : public Creator {
public:
	inline Unit* create() const override {
		return new Hero(72, 10, std::string("Slark"));
	}
};

class CreateHero_Butcher : public Creator {
public:
	inline Unit* create() const override {
		return new Hero(120, 6, std::string("Butcher"));
	}
};

class CreateMinion_Ragnaros : public Creator {
public:
	inline Unit* create() const override {
		return new Minion(1, 3, std::string("Ragnaros"));
	}
};

class CreateMinion_Bloodmage : public Creator {
public:
	inline Unit* create() const override {
		return new Minion(1, 1, std::string("Bloodmage"));
	}
};

class CreateMinion_Techies : public Creator {
public:
	inline Unit* create() const override {
		return new Minion(2, 1, std::string("Techies"));
	}
};

class CreateShaman_Flametongue : public Creator {
public:
	inline Unit* create() const override {
		return new Shaman(3, 0, std::string("Flametongue"));
	}
};

