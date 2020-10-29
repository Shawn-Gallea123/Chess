#pragma once

class Board;

#include <utility>

class Opponent {
public:
	enum class Difficulty {
		EASY,
		MEDIUM,
		HARD,
		EXPERT,
	};

	Opponent(Difficulty difficulty, Board* board);

	void MakeMove();

private:
	bool RandomPieceRandomSpot(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot);
	bool RandomPieceFavourAttacks(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot);

	Difficulty difficulty_;
	Board* board_;
};