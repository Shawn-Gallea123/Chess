#pragma once

class Board;

class Display {
public:
	Display();
	virtual ~Display();

	void SetBoard(Board* board);

	virtual bool DrawBoard() = 0;

protected:
	Board* board_ = nullptr;
};