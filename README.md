"This project is now have many coding issue. Anyway, it worked."
This is a game bases on "HearthStones: Heroes of Warcraft" game of Blizzard.

GAMEPLAY:
Bellow is the game requierments that I followed up:
-----------------------------------------------------------------------------------------------------------------
The game shall allow 2 players play turn by turn.														
There are 2 heroes in the game: Butcher and Slark.														
	Butcher has 120 HP and 6 Attack.													
	Slark has 72 HP and 10 Attack.													
There are 5 types of card:														
	Ragnaros the Firelord - A minion with 1HP and 3 Attack.													
	Bloodmage Thalnos - A minion with 1HP and 1 Attack.													
	Flametongue Totem - A shaman with 3HP and 0 Attack, but provides all alliance minions with a +1 Attack bonus.													
	Brawl - Destroy a random minion of the opposite player - Just use only 1 time.													
	Techies - A minion with 2HP and 1 Attack. On dead it deals 3 damages to both heros.													
Enter the game, each player is random a hero and 10 cards from the board (player is able to hold card of the same type).														
Each turn, a player can activate a card and place it into the battle. The card take effect immediately from that turn.														
When an unit has 0 HP, it's removed from the battle, player lose that card.														
A hero only attack the other hero. Minion/shaman deals damage to all units.														
Player is defeated when his hero has 0 HP.														
When a turn finishes, player shall be able to see remaining HP and Attack of all units in the battle.														
														
Example:
Assume that player 1 and player 2 have the following hero and cards and player 1 goes first.
	Player 1: Butcher, 2 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 1 Techies
	Player 2: Slark, 1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 2 Techies													
Turn 0 (Game start):														
	Board: Empty													
	Player 1: 120HP (2 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 1 Techies)													
	Player 2: 72HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 2 Techies)													
Turn 1, player 1 actives Ragnaros: Butcher reduces Slark by 6 HP, Ragnaros reduces Slark by 3 HP.														
	Board: Ragnaros(P1 - 1HP)													
	Player 1: 120HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 1 Techies)													
	Player 2: 63HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 2 Techies)													
Turn 2, player 2 actives Ragnaros: Slark reduces Butcher by 10 HP, Ragnaros reduces Butcher by 3HP. Ragnaros reduces Butcher's Ragnaros by 3HP, Butcher's Ragnaros is destroyed.														
	Board: Ragnaros(P2 - 1HP)													
	Player 1: 107HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Brawl, 1 Techies)													
	Player 2: 63HP (2 Bloodmage, 4 Flametongue, 1 Brawl, 2 Techies)													
Turn 3, player 1 actives Brawl: Butcher reduces Slark by 6 HP, Brawl destroys Ragnaros														
	Board: Empty													
	Player 1: 107HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Techies)													
	Player 2: 57HP (2 Bloodmage, 4 Flametongue, 1 Brawl, 2 Techies)													
Turn 4, player 2 actives Flametongue: Slark reduces Butcher by 10 HP														
	Board: Flametongue(P2 - 3HP)													
	Player 1: 97HP (1 Ragnaros, 2 Bloodmage, 4 Flametongue, 1 Techies)													
	Player 2: 57HP (2 Bloodmage, 3 Flametongue, 1 Brawl, 2 Techies)													
Turn 5, player 1 actives Flametongue: Butcher reduces Slark by 6 HP														
	Board: Flametongue(P2 - 3HP), Flametongue(P1 - 3HP)													
	Player 1: 97HP (1 Ragnaros, 2 Bloodmage, 3 Flametongue, 1 Techies)													
	Player 2: 51HP (2 Bloodmage, 3 Flametongue, 1 Brawl, 2 Techies)													
Turn 6, player 2 actives Flametongue: Slark reduces Butcher by 10 HP														
	Board: Flametongue(P2 - 3HP), Flametongue(P1 - 3HP), Flametongue(P2 - 3HP)													
	Player 1: 77HP (1 Ragnaros, 2 Bloodmage, 3 Flametongue, 1 Techies)													
	Player 2: 51HP (2 Bloodmage, 2 Flametongue, 1 Brawl, 2 Techies)													
Turn 7, player 1 actives Flametongue: Butcher reduces Slark by 6 HP														
	Board: Flametongue(P2 - 3HP), Flametongue(P1 - 3HP), Flametongue(P2 - 3HP), Flametongue(P1 - 3HP)													
	Player 1: 77HP (1 Ragnaros, 2 Bloodmage, 1 Flametongue, 1 Techies)													
	Player 2: 45HP (2 Bloodmage, 2 Flametongue, 1 Brawl, 2 Techies)													
Turn 8, player 2 actives Flametongue: Slark reduces Butcher by 10 HP														
	Board: Flametongue(P2 - 3HP), Flametongue(P1 - 3HP), Flametongue(P2 - 3HP), Flametongue(P1 - 3HP), Flametongue(P2 - 3HP)													
	Player 1: 67HP (1 Ragnaros, 2 Bloodmage, 1 Flametongue, 1 Techies)													
	Player 2: 45HP (2 Bloodmage, 1 Flametongue, 1 Brawl, 2 Techies)													
Turn 9, player 1 actives Ragnaros: Butcher reduces Slark by 6 HP, Ragnaros is added +2 Attack, Ragnaros reduces Slark by 5HP, Ragnaros reduces each minions of Slark by 5HP. All minions of Slark are destroyed.														
	Board: Flametongue(P1 - 3HP), Flametongue(P1 - 3HP), Ragnaros(P1 - 1HP)													
	Player 1: 67HP (2 Bloodmage, 1 Flametongue, 1 Techies)													
	Player 2: 34HP (2 Bloodmage, 1 Flametongue, 1 Brawl, 2 Techies)													
Turn 10, player 2 actives Techies: Slark reduces Butcher by 10 HP, Techies reduces Butcher by 1HP, Techies reduces each minions of Butcher by 1HP. Ragnaros of Slark is destroyed.														
	Board: Flametongue(P1 - 2HP), Flametongue(P1 - 2HP), Techies(P2 - 2HP)													
	Player 1: 56HP (2 Bloodmage, 1 Flametongue, 1 Techies)													
	Player 2: 34HP (2 Bloodmage, 1 Flametongue, 1 Brawl, 1 Techies)													
Turn 11, player 1 actives Techies: Butcher reduces Slark by 6 HP, Techies is added +2 Attack. Techies reduces Slark by 3HP, Techies reduces each minions of Slark by 3HP. Techies of Slark is destroyed and deal 3 damages to both heros														
	Board: Flametongue(P1 - 2HP), Flametongue(P1 - 2HP), Techies(P1 - 2HP)													
	Player 1: 53HP (2 Bloodmage, 1 Flametongue)													
	Player 2: 25HP (2 Bloodmage, 1 Flametongue, 1 Brawl, 1 Techies)													
Game continues...														
Note: You should find a way to print the output in an easy-to-read format
-----------------------------------------------------------------------------------------------------------------
