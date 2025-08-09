#include "Player.h"
class Unit;
Player::Player(const std::string& name)\
	: _name(name), _hero(nullptr), _isActive(false), _isWinner(Status::NA){
	createRandomHero();
	createRandomHandCards();
}

void Player::createRandomHero() {
	srand(static_cast<int>(time(NULL)));

	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	switch ((rand() % 2)) {
	case 0: {
		createPlayerHeroButcher();
		break;
	}
	case 1: {
		createPlayerHeroSlark();
		break;
	}
	default: break;
	}
}

void Player::createPlayerHeroButcher() {
	CreateHero_Butcher create_butcher;
	_hero = create_butcher.create();
}

void Player::createPlayerHeroSlark() {
	CreateHero_Slark create_slark;
	_hero = create_slark.create();
}

void Player::createRandomHandCards() {
	//srand(time(NULL));//not use
	CreateMinion_Ragnaros ragnarog;
	CreateMinion_Bloodmage bloodmage;
	CreateShaman_Flametongue flametongue;
	CreateMinion_Techies techies;
	CreateDestroyer_Brawl brawl;
	for (int i = 0; i < 10; i++) {
		switch ((rand() % 5)) {
		case 0: {
			_hand_cards.push_back(ragnarog.create());
			break;
		}
		case 1: {
			_hand_cards.push_back(bloodmage.create());
			break;
		}
		case 2: {
			_hand_cards.push_back(flametongue.create());
			break;
		}
		case 3: {
			_hand_cards.push_back(techies.create());
			break;
		}
		case 4: {
			_hand_cards.push_back(brawl.create());
			break;
		}
		default: break;
		}
	}
}

void Player::removeCardOnHand(unsigned int index) {
	if (index >= 0 && index < _hand_cards.size()) {
		_hand_cards.erase(_hand_cards.begin() + index);
		Notify();
	}
}

void Player::addCardToBoard(int index) {
	if (_hand_cards.size() != 0) {
		_board_cards.push_back(_hand_cards.at(index));
		removeCardOnHand(index);
		Notify();
	}
}

void Player::removeDeathCardOnBoard(Player& player) {
	for (int i = 0; i < player.getCardsOnBoard().size(); i++) {
		if ((player.getCardsOnBoard().at(i)->getHP()) == 0) {
			delete player.getCardsOnBoard().at(i);
			player.getCardsOnBoard().erase(player.getCardsOnBoard().begin() + i);
			i--;
		}
	}
	player.Notify();
}
//
void Player::activateOneCard(int index, Player& inactivePlayer, Player& activePlayer) {
	addCardToBoard(index);
	_board_cards.back()->spell(activePlayer.getHero(), inactivePlayer.getHero(), inactivePlayer.getCardsOnBoard(), activePlayer.getCardsOnBoard());
	if (activePlayer.getCardsOnBoard().size() != 0) {
		int added_dmg = 0;
		for (auto& card : activePlayer.getCardsOnBoard()) {
			switch (card->getType()) {
			case UnitType::SHAMAN:
			{
				added_dmg++;
				break;
			}
			case UnitType::HERO:
			case UnitType::MINION:
			case UnitType::DESTROYER:
			case UnitType::UNKNOWN:
			default:
				break;
			}
		}
		if (activePlayer.getCardsOnBoard().back()->getType() == UnitType::MINION) {
			activePlayer.getCardsOnBoard().back()->setDmg(activePlayer.getCardsOnBoard().back()->getDmg() + added_dmg);
			std::cout << "Total bonus damage: " << activePlayer.getCardsOnBoard().back()->getDmg() << std::endl;
		}
	}
	_board_cards.back()->attack(inactivePlayer.getHero(), inactivePlayer.getCardsOnBoard());
	callSpellOfDeadTechies(activePlayer, inactivePlayer);
	removeDeathCardOnBoard(inactivePlayer);
	removeDeathCardOnBoard(activePlayer);
	activeHeroAttackEnemyHero(inactivePlayer);
}

//check whether any dead techies _ if yes, call spell func of each techies
void Player::callSpellOfDeadTechies(Player& activePlayer, Player& inactivePlayer) {
	std::string techies = "Techies";
	int nDeadTechies = 0;
	for (auto& card : inactivePlayer.getCardsOnBoard()) {
		if (card->getName() == techies && card->isAlive() == false) {
			card->spell(activePlayer.getHero(), inactivePlayer.getHero(), inactivePlayer.getCardsOnBoard(), activePlayer.getCardsOnBoard());
		}
	}
}

void Player::activeHeroAttackEnemyHero(Player& inactivePlayer) {
	if (inactivePlayer.getHero().getHP() > 0) {
		int active_hero_dmg = this->_hero->getDmg();
		int inActive_hero_HP = inactivePlayer.getHero().getHP();
		int inActive_hero_new_HP = inActive_hero_HP - active_hero_dmg;
		(inActive_hero_new_HP > 0) ? inactivePlayer.getHero().setHP(inActive_hero_new_HP) : inactivePlayer.getHero().setHP(0);
	}
}

void Player::Attach(IObserver* observer) {
	list_observer_.push_back(observer);
}
void Player::Detach(IObserver* observer) {
	list_observer_.remove(observer);
}
void Player::Notify() {
	std::list<IObserver*>::iterator iterator = list_observer_.begin();
	while (iterator != list_observer_.end()) {
		(*iterator)->Update(*this);
		++iterator;
	}
}

const std::string& Player::getPlayerName() const {
	return _name;
}

Unit& Player::getHero() const {
	return *_hero;
}

bool Player::getActiveStatus() const {
	return _isActive;
}

Status Player::isWinnerOfGame() const {
	return _isWinner;
}

std::vector<Unit*>& Player::getCardsOnHand() {
	return _hand_cards;
}

std::vector<Unit*>& Player::getCardsOnBoard() {
	return _board_cards;
}

void Player::setActiveStatus(bool isActive) {
	_isActive = isActive;
	Notify();
}
void Player::setWinnerOfTheGame(Status isWinner) {
	_isWinner = isWinner;
	Notify();
}

void Player::printPlayerHandCards() {
	if (_hand_cards.size() != 0)
	{
		for (auto i : _hand_cards) {
			std::cout << i->getName() << " ";
		}
	}
}

Player::~Player() {
	for (std::vector<Unit*>::iterator itr = _hand_cards.begin(); itr != _hand_cards.end(); itr++)
	{
		if (*itr != nullptr) {
			delete* itr;
			*itr = nullptr;
		}
	}

	for (std::vector<Unit*>::iterator itr = _board_cards.begin(); itr != _board_cards.end(); itr++)
	{
		if (*itr != nullptr) {
			delete* itr;
			*itr = nullptr;
		}
	}

	/*for (std::list<IObserver*>::iterator itr = list_observer_.begin(); itr != list_observer_.end(); itr++)
	{
		if (*itr != nullptr) {
			delete* itr;
			*itr = nullptr;
		}
	}*/

	delete _hero;
}