#pragma once
#include "Unit.h"
#include "Hero.h"
#include "Minion.h"
#include "Shaman.h"
#include "Destroyer.h"

class Creator {
public:
	virtual ~Creator() {}
	virtual Unit* FactoryMethod() const = 0;
};

class CreateDestroyer_Brawl : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Destroyer(0, 0, "Brawl  ");
	}
};

class CreateHero_Slark : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Hero(72, 10, "Slark");
	}
};

class CreateHero_Butcher : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Hero(120, 6, "Butcher");
	}
};

class CreateMinion_Ragnaros : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Minion(1, 3, "Ragnaros");
	}
};

class CreateMinion_Bloodmage : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Minion(1, 1, "Bloodmage");
	}
};

class CreateMinion_Techies : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Minion(2, 1, "Techies");
	}
};

class CreateShaman_Flametongue : public Creator {
public:
	Unit* FactoryMethod() const override {
		return new Shaman(3, 0, "Flametongue");
	}
};

