#pragma once

#include "Piece.h"

class Rook : public Piece {
public:
	char GetSymbol() override;
	std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board, bool attacks_only) const override;

private:
	using Piece::Piece;
};