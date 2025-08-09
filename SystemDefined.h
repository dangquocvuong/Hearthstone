#pragma once
#pragma once
enum Status {
	WINNER = 1,
	LOSER = 2,
	NA = 0
};

enum UnitStatus {
	INACTIVE = 1,
	ACTIVE = 2,
	DEATH = 0
};

enum UnitType {
	HERO = 1,
	MINION = 2,
	SHAMAN = 3,
	DESTROYER = 4,
	UNKNOWN = 0
};