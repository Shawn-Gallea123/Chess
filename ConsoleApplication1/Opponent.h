#pragma once

class Board;

class Opponent {
public:
	enum class Difficulty {
		EASY,
		MEDIUM,
		HARD,
		EXPERT,
	};

	Opponent(Difficulty difficulty, Board* board);

private:
	Difficulty difficulty_;
	Board* board_;
};