#include "Knight.h"

int Knight::white_texture_ = -1;
int Knight::black_texture_ = -1;

Knight::Knight(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_knight.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_knight.png");
}

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

int Knight::GetTexture() {
	if (team_ == Team::WHITE)
		return white_texture_;
	else
		return black_texture_;
}