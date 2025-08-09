#pragma once
#include <iostream>
#include "Player.h"
#include "IObserver.h"
#include <stdlib.h>
#include <cstdio>

class GameMananger : public IObserver {
private:
	std::vector<Player*> _players;
public:
	GameMananger();
	~GameMananger();

	Player& getPlayerHasCardOnHand();
	Player& getPlayerNoCardOnHand();

	void startGame();
	void endGame();
	void printWinnerOfTheGame();
	void setWinner();
	void endTurnSwitchActiveStatus();
	void initializeNewGame();
	void createPlayers();
	void registerToObserverPlayersAndItsCards();
	void Update(const Player& players) override;
	void UpdateUnitChange(const Unit& units) override;
	void printBaseInfo() const;

	int letUserChooseCardOnPlayerHand();
	int getHandCardsOfActivePlayer() const;

	bool isAllHeroAlive();
	bool isBothPlayersHasCardOnHand();
	bool isOneOfPlayersHasCardOnHand();
	bool isBothPlayerOutOfHandCards();

	const std::string& getNameActivePlayer() const;

	Player& getActivePlayer();
	Player& getInactivePlayer();


	const std::vector<Player*>& getPlayers() const;
};