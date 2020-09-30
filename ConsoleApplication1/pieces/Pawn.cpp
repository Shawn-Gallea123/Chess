#include "Pawn.h"

#include "../Board.h"

char Pawn::GetSymbol() {
	return 'P';
}

std::vector<std::pair<int, int>> Pawn::GetPossibleMovementSpots(const Board* board) const {
	std::vector<std::pair<int, int>> spots;
	int direction = team_ == Team::WHITE ? 1 : -1;
	int step = y_ + direction;
	int step2 = y_ + direction * 2;

	// Pawn is at edge.
	if (step > 7 || step < 0)
		return spots;

	// Left attack
	if (x_ > 0 && board->GetPiece(x_ - 1, step) && board->GetPiece(x_ - 1, step)->GetTeam() != team_)
		spots.emplace_back(x_ - 1, step);

	// Right attack
	if (x_ < 8 && board->GetPiece(x_ + 1, step) && board->GetPiece(x_ + 1, step)->GetTeam() != team_)
		spots.emplace_back(x_ + 1, step);

	// Step
	if (!board->GetPiece(x_, step)) {
		spots.emplace_back(x_, step);
		// Double step
		if (!moved_ && !board->GetPiece(x_, step2))
			spots.emplace_back(x_, step2);
	}

	return spots;
}

void Pawn::OnMoved(int x, int y) {
	Piece::OnMoved(x, y);
	moved_ = true;
}