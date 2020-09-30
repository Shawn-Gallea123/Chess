#pragma once

#include "../Board.h"

class Display {
public:
	virtual void DrawBoard(const Board& board) = 0;
};