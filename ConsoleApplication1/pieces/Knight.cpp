#include "Knight.h"

char Knight::GetSymbol() {
	return 'N';
}

std::vector<std::pair<int, int>> Knight::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
	std::vector<std::pair<int, int>> spots;

	// Right
	CheckSpace(x_ + 2, y_ + 1, spots, board);
	CheckSpace(x_ + 2, y_ - 1, spots, board);

	// Up
	CheckSpace(x_ + 1, y_ + 2, spots, board);
	CheckSpace(x_ - 1, y_ + 2, spots, board);

	// Left
	CheckSpace(x_ - 2, y_ + 1, spots, board);
	CheckSpace(x_ - 2, y_ - 1, spots, board);

	// Down
	CheckSpace(x_ - 1, y_ - 2, spots, board);
	CheckSpace(x_ + 1, y_ - 2, spots, board);

	return spots;
}