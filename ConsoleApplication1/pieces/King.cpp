#include "King.h"

char King::GetSymbol() {
	return 'K';
}

std::vector<std::pair<int, int>> King::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
	std::vector<std::pair<int, int>> spots;
	CheckSpace(x_ + 1, y_, spots, board);
	CheckSpace(x_, y_ + 1, spots, board);
	CheckSpace(x_ - 1, y_, spots, board);
	CheckSpace(x_, y_ - 1, spots, board);
	return spots;
}