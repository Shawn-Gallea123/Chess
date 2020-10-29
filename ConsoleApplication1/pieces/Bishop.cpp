#include "Bishop.h"

#include <iostream>

#include "../Board.h"

int Bishop::white_texture_ = -1;
int Bishop::black_texture_ = -1;

Bishop::Bishop(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_bishop.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_bishop.png");
}

char Bishop::GetSymbol() {
	return 'B';
}

std::vector<std::pair<int, int>> Bishop::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
	std::vector<std::pair<int, int>> spots;
	
	// North-West
	for (int x = x_ + 1, y = y_ + 1; x < 8 && y < 8; ++x, ++y) {
		if (!CheckSpace(x, y, spots, board, attacks_only))
			break;
	}

	// South-East
	for (int x = x_ + 1, y = y_ - 1; x < 8 && y >= 0; ++x, --y) {
		if (!CheckSpace(x, y, spots, board, attacks_only))
			break;
	}

	// South-West
	for (int x = x_ - 1, y = y_ - 1; x >= 0 && y >= 0; --x, --y) {
		if (!CheckSpace(x, y, spots, board, attacks_only))
			break;
	}

	// North-West
	for (int x = x_ - 1, y = y_ + 1; x >= 0 && y < 8; --x, ++y) {
		if (!CheckSpace(x, y, spots, board, attacks_only))
			break;
	}
	return spots;
}

int Bishop::GetTexture() {
	if (team_ == Team::WHITE)
		return white_texture_;
	else
		return black_texture_;
}