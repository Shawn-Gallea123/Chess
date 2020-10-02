#pragma once

#include <memory>

#include "Board.h"
#include "display/Display.h"
#include "Opponent.h"

class Chess {
public:
	Chess();

	void Run();

private:
	void ChooseDifficulty();
	bool WhiteTurn();
	void BlackTurn();

	std::unique_ptr<Board> board_;
	std::unique_ptr<Opponent> opponent_;

	std::unique_ptr<Display> display_;
};