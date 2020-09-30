#pragma once

#include "Piece.h"

class Knight : public Piece {
public:
	char GetSymbol() override;
	std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board) const override;

private:
	using Piece::Piece;
};