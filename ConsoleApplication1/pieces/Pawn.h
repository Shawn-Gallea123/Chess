#pragma once

#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(int x, int y, Team team);

	char GetSymbol() override;
	std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board, bool attacks_only) const override;
	int GetTexture() override;
	void OnMoved(int x, int y) override;

private:
	bool moved_ = false;
	static int white_texture_;
	static int black_texture_;
};