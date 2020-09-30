#pragma once

#include <memory>
#include <vector>

#include "pieces/Piece.h"

class Board {
public:
	Board();
	~Board();

	void PrintBoard();
	bool Move(int x, int y, int dest_x, int dest_y);
	Piece* GetPiece(int x, int y) const;

private:
	void Setup();
	void AddPawns();
	void AddRooks();
	void AddKnights();
	void AddBishops();
	void AddQueen();
	void AddKing();

	bool CanMove(int x, int y, const Piece* piece) const;

	std::vector<std::vector<Piece*>> board_;
};