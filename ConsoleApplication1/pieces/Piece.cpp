#include "Piece.h"

#include "../Board.h"

Piece::Piece(int x, int y, Team team) 
	: x_(x), y_(y), team_(team) {}

Piece::~Piece() {}

Piece::Team Piece::GetTeam() {
	return team_;
}

void Piece::OnMoved(int x, int y) {
	x_ = x;
	y_ = y;
}

bool Piece::CheckSpace(int x, int y, std::vector<std::pair<int, int>>& spots, const Board* board) const {
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return false;
	Piece* piece = board->GetPiece(x, y);
	if (piece && piece->GetTeam() != team_) {
		spots.emplace_back(x, y);
		return false;
	}
	else if (!piece) {
		spots.emplace_back(x, y);
		return true;
	}
	else {
		return false;
	}
}

int Piece::GetX() {
	return x_;
}

int Piece::GetY() {
	return y_;
}