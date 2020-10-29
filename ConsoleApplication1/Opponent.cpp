#include "Opponent.h"

#include <iostream>
#include <stdlib.h>

#include "Board.h"

Opponent::Opponent(Difficulty difficulty, Board* board) : difficulty_(difficulty), board_(board) {}

void Opponent::MakeMove() {
	// TODO: What if they can't move at all?
	std::pair<int, int> starting_spot;
	std::pair<int, int> destination_spot;
	switch (difficulty_) {
	case Opponent::Difficulty::EASY:
		if (!RandomPieceRandomSpot(starting_spot, destination_spot))
			return;
		break;
	case Opponent::Difficulty::MEDIUM:
		break;
	case Opponent::Difficulty::HARD:
		break;
	case Opponent::Difficulty::EXPERT:
		break;
	}
	board_->Move(starting_spot.first, starting_spot.second, destination_spot.first, destination_spot.second);
}

bool Opponent::RandomPieceRandomSpot(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot) {
	auto blacks = board_->GetBlacks();
	while (true) {
		if (blacks.size() == 0)
			return false;
		int random_piece_index = rand() % blacks.size();
		auto random_piece = blacks.at(random_piece_index);
		auto movement_spots = random_piece->GetPossibleMovementSpots(board_, false);
		
		if (movement_spots.size() == 0) {
			blacks.erase(blacks.begin() + random_piece_index);
		} else {
			auto random_spot = movement_spots.at(rand() % movement_spots.size());
			starting_spot = std::pair<int, int>(random_piece->GetX(), random_piece->GetY());
			destination_spot = std::pair<int, int>(random_spot.first, random_spot.second);
			return true;
		}
	}
}