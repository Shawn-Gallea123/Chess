#include "Pawn.h"

#include "../Board.h"

int Pawn::white_texture_ = -1;
int Pawn::black_texture_ = -1;

Pawn::Pawn(int x, int y, Team team) : Piece(x, y, team) {
	if (white_texture_ == -1)
		white_texture_ = Generate2DTexture("sprites/white_pawn.png");
	if (black_texture_ == -1)
		black_texture_ = Generate2DTexture("sprites/black_pawn.png");
}

char Pawn::GetSymbol() {
	return 'P';
}

std::vector<std::pair<int, int>> Pawn::GetPossibleMovementSpots(const Board* board, bool attacks_only) const {
	std::vector<std::pair<int, int>> spots;
	int direction = team_ == Team::WHITE ? 1 : -1;
	int step = y_ + direction;
	int step2 = y_ + direction * 2;

	// Pawn is at edge.
	if (step > 7 || step < 0)
		return spots;

	// Left attack
	if (x_ - 1 > 0 && board->GetPiece(x_ - 1, step) && board->GetPiece(x_ - 1, step)->GetTeam() != team_)
		spots.emplace_back(x_ - 1, step);

	// Right attack
	if (x_ + 1 < 8 && board->GetPiece(x_ + 1, step) && board->GetPiece(x_ + 1, step)->GetTeam() != team_)
		spots.emplace_back(x_ + 1, step);

	if (attacks_only)
		return spots;

	// Step
	if (!board->GetPiece(x_, step)) {
		spots.emplace_back(x_, step);
		// Double step
		if (!moved_ && !board->GetPiece(x_, step2))
			spots.emplace_back(x_, step2);
	}

	return spots;
}

int Pawn::GetTexture() {
	if (team_ == Team::WHITE)
		return white_texture_;
	else
		return black_texture_;
}

void Pawn::OnMoved(int x, int y) {
	Piece::OnMoved(x, y);
	moved_ = true;
}