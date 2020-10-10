#pragma once

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, Team team);

	char GetSymbol() override;
	std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board, bool attacks_only) const override;

private:
	static int white_texture_;
	static int black_texture_;
};