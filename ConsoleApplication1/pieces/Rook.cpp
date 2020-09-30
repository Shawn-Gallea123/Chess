#include "Rook.h"

#include "../Board.h"
#include "Piece.h"

char Rook::GetSymbol() {
	return 'R';
}

std::vector<std::pair<int, int>> Rook::GetPossibleMovementSpots(const Board* board) const {
	std::vector<std::pair<int, int>> spots;
	
	// Right
	for (int x = x_ + 1; x < 8; ++x) {
		if (!CheckSpace(x, y_, spots, board))
			break;
	}

	// Left
	for (int x = x_ - 1; x >= 0; --x) {
		if (!CheckSpace(x, y_, spots, board))
			break;
	}

	// Up
	for (int y = y_ + 1; y < 8; ++y) {
		if (!CheckSpace(x_, y, spots, board))
			break;
	}

	// Down
	for (int y = y_ - 1; y >= 0; --y) {
		if (!CheckSpace(x_, y, spots, board))
			break;
	}

	return spots;
}