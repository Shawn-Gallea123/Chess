#pragma once

#include <memory>

#include "Board.h"
#include "Opponent.h"

class Chess {
public:
	Chess();

	void Run();

private:
	void ChooseDifficulty();
	bool WhiteTurn();
	void BlackTurn();
	void CheckForChecks();

	std::unique_ptr<Board> board_;
	std::unique_ptr<Opponent> opponent_;
};