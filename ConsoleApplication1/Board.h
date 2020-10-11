#pragma once

#include <memory>
#include <vector>

#include "pieces/Piece.h"

class Board {
public:
	Board();
	~Board();

	bool Move(int x, int y, int dest_x, int dest_y);
	Piece* GetPiece(int x, int y) const;
	bool CheckForChecks(Piece::Team team);
	void SelectTile(int x, int y);
	const std::pair<int, int>* GetSelectedTile();

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
	std::unique_ptr<std::pair<int, int>> selected_tile_;
};