#include "Opponent.h"

#include <iostream>
#include <stdlib.h>

#include "Board.h"

Opponent::Opponent(Difficulty difficulty, Board* board) : difficulty_(difficulty), board_(board) {}

void Opponent::MakeMove() {
	std::pair<int, int> starting_spot;
	std::pair<int, int> destination_spot;
	switch (difficulty_) {
	case Opponent::Difficulty::EASY:
		RandomPieceRandomSpot(starting_spot, destination_spot);
		break;
	case Opponent::Difficulty::MEDIUM:
		break;
	case Opponent::Difficulty::HARD:
		break;
	case Opponent::Difficulty::EXPERT:
		break;
	}
}

void Opponent::RandomPieceRandomSpot(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot) {
	auto blacks = board_->GetBlacks();
	while (true) {
		if (blacks.size() == 0)
			return;
		int random_piece_index = rand() % blacks.size();
		std::cout << "random piece index: " << random_piece_index << std::endl;
		auto random_piece = blacks.at(random_piece_index);
		auto movement_spots = random_piece->GetPossibleMovementSpots(board_, false);
		std::cout << "Movement spots size: " << movement_spots.size() << std::endl;
		
		if (movement_spots.size() == 0) {
			std::cout << "IF" << std::endl;
			blacks.erase(blacks.begin() + random_piece_index);
		} else {
			std::cout << "ELSE" << std::endl;
			auto random_spot = movement_spots.at(rand() % movement_spots.size());
			board_->Move(random_piece->GetX(), random_piece->GetY(), random_spot.first, random_spot.second);
			break;
		}
	}
}