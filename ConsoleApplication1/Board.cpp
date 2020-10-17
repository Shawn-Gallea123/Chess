#include "Board.h"

#include <algorithm>
#include <iostream>
#include <memory>

#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Board::Board(Opponent::Difficulty difficulty) 
	: opponent_(std::make_unique<Opponent>(difficulty, this)){
	board_.resize(8);
	for (auto& column : board_)
		column.resize(8);

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			board_[i][j] = nullptr;

	Setup();
}

Board::~Board() {
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			delete board_[i][j];
}

bool Board::Move(int x, int y, int dest_x, int dest_y) {
	Piece* piece = board_[x][y];
	if (x < 0 || x > 7 || y < 0 || y > 7 || dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7 || !piece)
		return false;
	std::pair<int, int> destination{ dest_x, dest_y };
	auto possible_movement_spots = piece->GetPossibleMovementSpots(this, false);
	if (std::find(possible_movement_spots.begin(), possible_movement_spots.end(), destination) != possible_movement_spots.end()) {
		Piece* deleted_piece = board_[dest_x][dest_y];
		board_[dest_x][dest_y] = piece;
		board_[x][y] = nullptr;
		piece->OnMoved(dest_x, dest_y);

		// If other piece existed on this space, remove from pieces vector
		if (deleted_piece) {
			std::vector<Piece*>& pieces_list = deleted_piece->GetTeam() == Piece::Team::WHITE ? whites_ : blacks_;
			auto position = std::find(pieces_list.begin(), pieces_list.end(), deleted_piece);
			if (position != pieces_list.end())
				pieces_list.erase(position);
			delete deleted_piece;
		}

		return true;
	}
	return false;
}

Piece* Board::GetPiece(int x, int y) const {
	return board_[x][y];
}

void Board::Setup() {
	AddPawns();
	AddRooks();
	AddKnights();
	AddBishops();
	AddQueen();
	AddKing();
}

void Board::AddPawns() {
	for (int i = 0; i < 8; ++i) {
		board_[i][1] = new Pawn(i, 1, Piece::Team::WHITE);
		whites_.emplace_back(board_[i][1]);
		board_[i][6] = new Pawn(i, 6, Piece::Team::BLACK);
		blacks_.emplace_back(board_[i][6]);
	}
}

void Board::AddRooks() {
	board_[0][0] = new Rook(0, 0, Piece::Team::WHITE);
	board_[7][0] = new Rook(7, 0, Piece::Team::WHITE);
	whites_.emplace_back(board_[0][0]);
	whites_.emplace_back(board_[7][0]);
	board_[0][7] = new Rook(0, 7, Piece::Team::BLACK);
	board_[7][7] = new Rook(7, 7, Piece::Team::BLACK);
	blacks_.emplace_back(board_[0][7]);
	blacks_.emplace_back(board_[7][7]);
}

void Board::AddKnights() {
	board_[1][0] = new Knight(1, 0, Piece::Team::WHITE);
	board_[6][0] = new Knight(6, 0, Piece::Team::WHITE);
	whites_.emplace_back(board_[1][0]);
	whites_.emplace_back(board_[6][0]);
	board_[1][7] = new Knight(1, 7, Piece::Team::BLACK);
	board_[6][7] = new Knight(6, 7, Piece::Team::BLACK);
	blacks_.emplace_back(board_[1][7]);
	blacks_.emplace_back(board_[6][7]);
}

void Board::AddBishops() {
	board_[2][0] = new Bishop(2, 0, Piece::Team::WHITE);
	board_[5][0] = new Bishop(5, 0, Piece::Team::WHITE);
	whites_.emplace_back(board_[2][0]);
	whites_.emplace_back(board_[5][0]);
	board_[2][7] = new Bishop(2, 7, Piece::Team::BLACK);
	board_[5][7] = new Bishop(5, 7, Piece::Team::BLACK);
	blacks_.emplace_back(board_[2][7]);
	blacks_.emplace_back(board_[5][7]);
}

void Board::AddQueen() {
	board_[4][0] = new Queen(4, 0, Piece::Team::WHITE);
	whites_.emplace_back(board_[4][0]);
	board_[4][7] = new Queen(4, 7, Piece::Team::BLACK);
	blacks_.emplace_back(board_[4][7]);
}

void Board::AddKing() {
	board_[3][0] = new King(3, 0, Piece::Team::WHITE);
	whites_.emplace_back(board_[3][0]);
	white_king_ = board_[3][0];
	board_[3][7] = new King(3, 7, Piece::Team::BLACK);
	blacks_.emplace_back(board_[3][7]);
	black_king_ = board_[3][7];
}

bool Board::CanMove(int x, int y, const Piece* piece) const {
	auto spots = piece->GetPossibleMovementSpots(this, false);
	return std::find(spots.begin(), spots.end(), std::pair<int, int>(x, y)) != spots.end();
}

bool Board::CheckForChecks(Piece::Team team) {
	bool is_white_king = team == Piece::Team::WHITE;
	Piece* king = is_white_king ? white_king_ : black_king_;
	auto pieces = is_white_king ? blacks_ : whites_;

	for (Piece* piece : pieces) {
		auto spots = piece->GetPossibleMovementSpots(this, true);
		std::pair<int, int> king_spot = std::pair<int, int>(king->GetX(), king->GetY());
		// King is found on a movement spot, is in check
		if (std::find(spots.begin(), spots.end(), king_spot) != spots.end())
			return true;
	}
	return false;
}

void Board::OnClick(int x, int y) {
	auto previously_selected_piece = selected_tile_ ? board_[selected_tile_->first][selected_tile_->second] : nullptr;
	if (previously_selected_piece && CanMove(x, y, previously_selected_piece)) {
		Move(selected_tile_->first, selected_tile_->second, x, y);
		selected_tile_.reset();
		opponent_->MakeMove();
		return;
	}
	selected_tile_ = std::make_unique<std::pair<int, int>>(x, y);
	if (!board_[x][y] || board_[x][y]->GetTeam() != Piece::Team::WHITE) {
		selected_tile_.reset();
	}
}

const std::pair<int, int>* Board::GetSelectedTile() {
	return selected_tile_.get();
}

std::vector<Piece*> Board::GetBlacks() {
	return blacks_;
}