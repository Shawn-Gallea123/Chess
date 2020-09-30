#include "Bishop.h"

#include <iostream>

#include "../Board.h"

char Bishop::GetSymbol() {
	return 'B';
}

std::vector<std::pair<int, int>> Bishop::GetPossibleMovementSpots(const Board* board) const {
	std::vector<std::pair<int, int>> spots;
	
	// North-West
	for (int x = x_ + 1, y = y_ + 1; x < 8 && y < 8; ++x, ++y) {
		if (!CheckSpace(x, y, spots, board))
			break;
	}

	// South-East
	for (int x = x_ + 1, y = y_ - 1; x < 8 && y >= 0; ++x, --y) {
		if (!CheckSpace(x, y, spots, board))
			break;
	}

	// South-West
	for (int x = x_ - 1, y = y_ - 1; x >= 0 && y >= 0; --x, --y) {
		if (!CheckSpace(x, y, spots, board))
			break;
	}

	// North-West
	for (int x = x_ - 1, y = y_ + 1; x >= 0 && y < 8; --x, ++y) {
		if (!CheckSpace(x, y, spots, board))
			break;
	}
	return spots;
}