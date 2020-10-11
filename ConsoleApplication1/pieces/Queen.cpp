#include "Queen.h"

int Queen::white_texture_ = -1;
int Queen::black_texture_ = -1;

Queen::Queen(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_queen.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_queen.png");
}

char Queen::GetSymbol() {
	return 'Q';
}

std::vector<std::pair<int, int>> Queen::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
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

int Queen::GetTexture() {
	if (team_ == Team::WHITE)
		return white_texture_;
	else
		return black_texture_;
}