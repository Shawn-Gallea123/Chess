#include "Rook.h"

#include "../Board.h"
#include "Piece.h"

int Rook::white_texture_ = -1;
int Rook::black_texture_ = -1;

Rook::Rook(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_rook.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_rook.png");
}

char Rook::GetSymbol() {
	return 'R';
}

std::vector<std::pair<int, int>> Rook::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
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