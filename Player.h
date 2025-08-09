#pragma once
#include <string>
#include <vector>
#include "Unit.h"
#include <list>
#include "Hero.h"
#include "ISubject.h"
#include "IObserver.h"
#include <cstdlib>
#include <time.h>
#include "Creator.h"

//#include <unistd.h>
//#include<windows.h>
#include <thread>         
#include <chrono>
class Unit;

class Player : public ISubject {
private:
	std::string _name;
	Unit* _hero;
	std::vector<Unit*> _hand_cards;
	std::vector<Unit*> _board_cards;
	bool _isActive;
	Status _isWinner;//winner-loser

	std::list<IObserver*> list_observer_;
public:
	Player(const std::string& name);
	~Player();
	void createRandomHero();
	void createPlayerHeroButcher();
	void createPlayerHeroSlark();
	void createRandomHandCards();
	void removeCardOnHand(unsigned int index);
	void addCardToBoard(int index);
	void removeDeathCardOnBoard(Player& player);
	void activateOneCard(int index, Player& inactivePlayer, Player& activePlayer);
	void callSpellOfDeadTechies(Player& activePlayer, Player& inactivePlayer);
	void activeHeroAttackEnemyHero(Player& inactivePlayer);
	void Attach(IObserver* observer) override;
	void Detach(IObserver* observer) override;
	void Notify() override;
	void setActiveStatus(bool isActive);
	void setWinnerOfTheGame(Status isWinner);
	void printPlayerHandCards();

	const std::string& getPlayerName() const;
	bool getActiveStatus() const;
	Unit& getHero() const;
	Status isWinnerOfGame() const;

	std::vector<Unit*>& getCardsOnHand();
	std::vector<Unit*>& getCardsOnBoard();
};