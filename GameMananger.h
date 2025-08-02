#pragma once
#include <iostream>
#include "Player.h"
#include "IObserver.h"
#include <stdlib.h>
#include <stdio.h>

class GameMananger : public IObserver {
private:
	std::vector<Player*> _players;
	//int turn;
public:
	GameMananger() {
		//initializeNewGame();
	}

	void registerToPlayersAndItsCards() {
		if (_players.size() != 0) {
			for (std::vector<Player*>::const_iterator itr_player = _players.begin(); itr_player != _players.end(); itr_player++) {
				(*itr_player)->Attach(this);
				for (std::vector<Unit*>::const_iterator itr_unit = (*itr_player)->getCardsOnBoard().begin(); itr_unit != (*itr_player)->getCardsOnBoard().end(); itr_unit++) {
					(*itr_unit)->Attach(this);
				}
				for (std::vector<Unit*>::const_iterator itr_unit = (*itr_player)->getCardsOnHand().begin(); itr_unit != (*itr_player)->getCardsOnHand().end(); itr_unit++) {
					(*itr_unit)->Attach(this);
				}
			}
		}
	}

	void initializeNewGame() {
		this->createPlayers();
		this->printBaseInfo();
		this->registerToPlayersAndItsCards();
	}

	void startGame() {
		int index = 0;
		int input;
		while (isAllHeroAlive()) {
			std::cout << "Activating player: " << getNameActivePlayer() << std::endl;
			//both player has card on hand
			if (isBothPlayersHasCardOnHand()) {
				//std::cout << "TEST 1" << std::endl;
					//handle index base on user input: ex: input=1 <=> index=0; 
				input = letUserChooseCardOnPlayerHand();
				if (input != 0)
					index = input - 1;
				else
					index = 0;
				std::cout << "index" << index << std::endl;///

				//add card to board - erase that card on hand
				getActivePlayer().activateOneCard(index, getInactivePlayer(), getActivePlayer());
			}
			//One player has card on hand
			else if (isOneOfPlayersHasCardOnHand()) {
				if (getPlayerHasCardOnHand().getCardsOnHand().size() > 0) {
					//std::cout << "TEST 2: getPlayerHasCardOnHand().getCardsOnHand().size()" << getPlayerHasCardOnHand().getCardsOnHand().size() << std::endl;
					input = letUserChooseCardOnPlayerHand();
					if (input != 0)
						index = input - 1;
					else
						index = 0;
					std::cout << "index" << index << std::endl;///

					getPlayerHasCardOnHand().activateOneCard(index, getPlayerNoCardOnHand(), getPlayerHasCardOnHand());

				}
			}
			//both players have no hand card left
			else if (isBothPlayerOutOfHandCards()) {
				//std::cout << "TEST 3" << std::endl;
				if (getActivePlayer().getCardsOnBoard().size() > 0) {
					for (auto& i : getActivePlayer().getCardsOnBoard()) {
						i->attack(getInactivePlayer().getHero());
					}
					getActivePlayer().activeHeroAttackEnemyHero(getInactivePlayer());
				}

			}
			else {
				//std::cout << "TEST 4" << std::endl;
				getActivePlayer().activeHeroAttackEnemyHero(getInactivePlayer());

			}
			endTurnSwitchActiveStatus();
		}
	}

	bool isBothPlayerOutOfHandCards() {
		bool flag = true;
		for (auto& i : _players) {
			flag = flag && (i->getCardsOnHand().empty());
		}
		std::cout << "isBothPlayerOutOfHandCards()::flag = " << flag << std::endl;
		return flag;
	}


	Player& getPlayerHasCardOnHand() {
		for (auto& i : _players) {
			if (i->getCardsOnHand().size() > 0)
				return *i;
		}
	}

	Player& getPlayerNoCardOnHand() {
		for (auto& i : _players) {
			if (i->getCardsOnHand().size() <= 0)
				return *i;
		}
	}

	void endGame() {
		setWinner();
		printWinnerOfTheGame();
	}

	void printWinnerOfTheGame() {
		for (auto& player : _players) {
			if (player->isWinnerOfGame()) {
				std::cout << "Winner: " << player->getPlayerName() << std::endl;
			}
		}
	}

	void setWinner() {
		for (auto& player : _players) {
			if (player->getHero().getHP() > 0) {
				player->setWinnerOfTheGame(PlayerStatus::WINNER);
			}
		}
	}

	int letUserChooseCardOnPlayerHand() {
		int user_input;
		do {
			std::cout << "Choose card number in range [1:" << getActivePlayer().getCardsOnHand().size() << "]: ";
			std::cin >> user_input;
		} while (user_input <= 0 || user_input > getHandCardsOfActivePlayer());
		return user_input;
	}

	void createPlayers() {
		Player* player = new Player("Player1");
		player->setActiveStatus(true);
		_players.push_back(player);
		player = new Player("Player2");
		_players.push_back(player);
		//delete player; //x
		player = nullptr;
	}

	void endTurnSwitchActiveStatus() {
		if (_players.size() != 0) {
			for (auto i : _players) {
				if (i->getActiveStatus() == true)
					i->setActiveStatus(false);
				else
					i->setActiveStatus(true);
			}
		}
	}

	int getHandCardsOfActivePlayer() const {
		if (_players.size() != 0) {
			for (auto i : _players) {
				if (i->getActiveStatus() == true)
					return i->getCardsOnHand().size();
			}
		}
		else {
			std::cout << "VUONG: GameMananger::getHandCardsActivePlayer() _players.size()=0 " << std::endl;
			return 0;
		}
	}

	bool isBothPlayersHasCardOnHand() {
		bool flag = true;
		for (auto& i : _players) {
			//flag = flag && (!(i->getCardsOnHand().empty()));
			flag = flag && ((i->getCardsOnHand().size() > 0) ? true : false);
		}
		return flag; // true: all players has cards on hand
	}

	bool isOneOfPlayersHasCardOnHand() {
		for (auto& i : _players) {
			if (i->getCardsOnHand().size() > 0)
				return true;
		}
		return false; // true: all players has cards on hand
	}

	std::string getNameActivePlayer() const {
		for (auto& i : _players) {
			if (i->getActiveStatus() == true)
				return i->getPlayerName();
		}
	}

	Player& getActivePlayer() {
		for (auto& i : _players) {
			if (i->getActiveStatus() == true)
				return *i;
		}
	}

	Player& getInactivePlayer() {

		for (auto& i : _players) {
			if (i->getActiveStatus() == false)
				return *i;
		}

	}

	bool isAllHeroAlive() {
		bool temp = true;
		if (_players.size() != 0) {
			for (auto& i : _players) {
				temp = (temp && i->getHero().isAlive());
			}
		}
		return temp;
	}

	const std::vector<Player*>& getPlayers() const {
		std::cout << &_players << std::endl;
		return _players;
	}

	void Update(const Player& players) override {
		printBaseInfo();
	}

	void UpdateUnitChange(const Unit& units) override {
		printBaseInfo();
	}

//	void clearScreen()
//	{
//#ifdef _WIN32
//		std::system("cls");
//#else
//		std::system("clear");
//#endif
//	}

	void printBaseInfo() const {
		std::system("cls");
		int count = 1;
		std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		for (std::vector<Player*>::const_iterator itr_player = _players.begin(); itr_player != _players.end(); itr_player++) {
			if (itr_player == _players.begin()) {
				std::cout << (*itr_player)->getPlayerName() << "\t\t" << (*itr_player)->getHero().getName() << ": " << (*itr_player)->getHero().getHP() << "HP" << "\t" << (*itr_player)->getHero().getDmg() << "ATK" << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				std::cout << "OnHands:\t";
				//print name cards on hand
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << count << "." << (*itr_Unit_on_hand)->getName() << "\t";
						count++;
					}
				}
				std::cout << std::endl;
				std::cout << "\t\t";
				//print type of cards on hand
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << (*itr_Unit_on_hand)->typeToText() << "   \t";
					}
				}

				std::cout << std::endl;
				std::cout << "\t";
				//print attribute of cards on hand
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << "\t" << (*itr_Unit_on_hand)->getHP() << ".HP " << (*itr_Unit_on_hand)->getDmg() << ".ATK";
					}
				}

				std::cout << std::endl;
				std::cout << "\t\t----------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				std::cout << "OnBoard:\t";
				//print name cards on board
				count = 1;
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << count << "." << (*itr_Unit_on_board)->getName() << "\t";
						count++;
					}
				}

				std::cout << std::endl;
				std::cout << "\t\t";
				//print type of cards on board
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << (*itr_Unit_on_board)->typeToText() << "\t\t";
					}
				}

				std::cout << std::endl;
				std::cout << "\t";
				//print attribute of cards on board
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << "\t" << (*itr_Unit_on_board)->getHP() << ".HP " << (*itr_Unit_on_board)->getDmg() << ".ATK";
					}
				}
				std::cout << "\n\n" << std::endl;
			}
			else {
				count = 1;
				std::cout << "OnBoard:\t";
				//print name cards on board
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << count << "." << (*itr_Unit_on_board)->getName() << "\t";
						count++;
					}
				}

				std::cout << std::endl;
				std::cout << "\t\t";
				//print type of cards on board
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << (*itr_Unit_on_board)->typeToText() << "\t\t";
					}
				}

				std::cout << std::endl;
				std::cout << "\t";
				//print attribute of cards on board
				if (!(*itr_player)->getCardsOnBoard().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_board = (*itr_player)->getCardsOnBoard().begin(); itr_Unit_on_board != (*itr_player)->getCardsOnBoard().end(); itr_Unit_on_board++) {
						std::cout << "\t" << (*itr_Unit_on_board)->getHP() << ".HP " << (*itr_Unit_on_board)->getDmg() << ".ATK";
					}
				}

				std::cout << std::endl;
				std::cout << "\t\t----------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				std::cout << "OnHands:\t";
				//print name cards on hand
				count = 1;
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << count << "." << (*itr_Unit_on_hand)->getName() << "\t";
						count++;
					}
				}

				std::cout << std::endl;
				std::cout << "\t\t";
				//print type of cards on hand
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << (*itr_Unit_on_hand)->typeToText()<< "   \t";
					}
				}

				std::cout << std::endl;
				std::cout << "\t";
				//print attribute of cards on hand
				if (!(*itr_player)->getCardsOnHand().empty()) {
					for (std::vector<Unit*>::const_iterator itr_Unit_on_hand = (*itr_player)->getCardsOnHand().begin(); itr_Unit_on_hand != (*itr_player)->getCardsOnHand().end(); itr_Unit_on_hand++) {
						std::cout << "\t" << (*itr_Unit_on_hand)->getHP() << ".HP " << (*itr_Unit_on_hand)->getDmg() << ".ATK";
					}
				}

				std::cout << std::endl;
				std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				std::cout << (*itr_player)->getPlayerName() << "\t\t" << (*itr_player)->getHero().getName() << ": " << (*itr_player)->getHero().getHP() << "HP" << "\t" << (*itr_player)->getHero().getDmg() << "ATK" << std::endl;
			}
		}
		std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}

	~GameMananger() {
		//turn = 1;
		for (std::vector<Player*>::iterator itr_player = _players.begin(); itr_player != _players.end(); itr_player++) {
			delete* itr_player;
			*itr_player = nullptr;
		}
	}

};