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
		if (!RandomPieceFavourAttacks(starting_spot, destination_spot))
			return;
		break;
	case Opponent::Difficulty::HARD:
		if (!FavourAttacks(starting_spot, destination_spot))
			return;
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

bool Opponent::RandomPieceFavourAttacks(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot) {
	auto blacks = board_->GetBlacks();
	while (true) {
		if (blacks.size() == 0)
			return false;
		int random_piece_index = rand() % blacks.size();
		auto random_piece = blacks.at(random_piece_index);

		auto attack_spots = random_piece->GetPossibleMovementSpots(board_, true);
		auto movement_spots = random_piece->GetPossibleMovementSpots(board_, false);

		if (attack_spots.size() == 0 && movement_spots.size() == 0) {
			blacks.erase(blacks.begin() + random_piece_index);
		}
		else {
			auto& spots = attack_spots.size() != 0 ? attack_spots : movement_spots;
			auto random_spot = spots.at(rand() % spots.size());
			starting_spot = std::pair<int, int>(random_piece->GetX(), random_piece->GetY());
			destination_spot = std::pair<int, int>(random_spot.first, random_spot.second);
			return true;
		}
	}
}

bool Opponent::FavourAttacks(std::pair<int, int>& starting_spot, std::pair<int, int>& destination_spot) {
	auto blacks = board_->GetBlacks();
	std::vector<Piece*> attackable_pieces;

	for (auto piece : blacks) {
		if (!piece->GetPossibleMovementSpots(board_, true).empty()) {
			attackable_pieces.emplace_back(piece);
		}
	}

	if (attackable_pieces.empty())
		return RandomPieceRandomSpot(starting_spot, destination_spot);
	
	while (true) {
		if (attackable_pieces.size() == 0)
			return false;
		int random_piece_index = rand() % attackable_pieces.size();
		auto random_attackable_piece = attackable_pieces.at(random_piece_index);

		auto attack_spots = random_attackable_piece->GetPossibleMovementSpots(board_, true);

			auto random_spot = attack_spots.at(rand() % attack_spots.size());
			starting_spot = std::pair<int, int>(random_attackable_piece->GetX(), random_attackable_piece->GetY());
			destination_spot = std::pair<int, int>(random_spot.first, random_spot.second);
			return true;
	}
}