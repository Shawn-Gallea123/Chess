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
	bool CheckForChecks(Piece::Team team);

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
	std::vector<Piece*> whites_;
	Piece* white_king_;
	std::vector<Piece*> blacks_;
	Piece* black_king_;
};