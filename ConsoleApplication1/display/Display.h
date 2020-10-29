#pragma once

class Board;

class Display {
public:
	Display();
	virtual ~Display();

	void SetBoard(Board* board);

	virtual bool DrawBoard() = 0;
	virtual void OnPieceMoved(int x, int y, int dest_x, int dest_y) = 0;

protected:
	Board* board_ = nullptr;
};