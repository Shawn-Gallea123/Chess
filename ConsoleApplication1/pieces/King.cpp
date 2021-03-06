#include "King.h"

int King::white_texture_ = -1;
int King::black_texture_ = -1;

King::King(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_king.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_king.png");
}

char King::GetSymbol() {
	return 'K';
}

std::vector<std::pair<int, int>> King::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
	std::vector<std::pair<int, int>> spots;
	CheckSpace(x_, y_ + 1, spots, board, attacks_only); // top
	CheckSpace(x_ + 1, y_ + 1, spots, board, attacks_only); // top-right
	CheckSpace(x_ + 1, y_, spots, board, attacks_only); // right
	CheckSpace(x_ + 1, y_ - 1, spots, board, attacks_only); // bottom-right
	CheckSpace(x_, y_ - 1, spots, board, attacks_only); // bottom
	CheckSpace(x_ - 1, y_ - 1, spots, board, attacks_only); // bottom-left
	CheckSpace(x_ - 1, y_, spots, board, attacks_only); // left
	CheckSpace(x_ - 1, y_ + 1, spots, board, attacks_only); // top-left
	return spots;
}

int King::GetTexture() {
	if (team_ == Team::WHITE)
		return white_texture_;
	else
		return black_texture_;
}