#pragma once

#include "Piece.h"

class Pawn : public Piece {
public:
	char GetSymbol() override;
	std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board) const override;
	void OnMoved(int x, int y) override;

private:
	using Piece::Piece;

	bool moved_ = false;
};