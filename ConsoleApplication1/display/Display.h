#pragma once

class Board;

class Display {
public:
	Display(Board* board);
	virtual ~Display();

	virtual void DrawBoard() = 0;

protected:
	Board* board_;
};