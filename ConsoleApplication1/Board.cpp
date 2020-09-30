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

Board::Board() {
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

void Board::PrintBoard() {
	for (int i = 0; i < 16; ++i)
		std::cout << '-';
	std::cout << std::endl;
	for (int y = 7; y >= 0; --y)
		for (int x = 0; x < 8; ++x) {
			if (x == 0)
				std::cout << '|';

			if (board_[x][y])
				std::cout << board_[x][y]->GetSymbol();
			else
				std::cout << '.';

			if (x == 7) {
				std::cout << '|' << std::endl;
				for (int i = 0; i < 16; ++i)
					std::cout << '-';
				std::cout << std::endl;
			}
			else
				std::cout << '|';
		}
}

bool Board::Move(int x, int y, int dest_x, int dest_y) {
	Piece* piece = board_[x][y];
	if (x < 0 || x > 7 || y < 0 || y > 7 || dest_x < 0 || dest_x > 7 || dest_y < 0 || dest_y > 7 || !piece)
		return false;
	std::pair<int, int> destination{ dest_x, dest_y };
	auto possible_movement_spots = piece->GetPossibleMovementSpots(this);
	if (std::find(possible_movement_spots.begin(), possible_movement_spots.end(), destination) != possible_movement_spots.end()) {
		delete board_[dest_x][dest_y];
		board_[dest_x][dest_y] = piece;
		board_[x][y] = nullptr;
		piece->OnMoved(dest_x, dest_y);
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
		board_[i][6] = new Pawn(i, 6, Piece::Team::BLACK);
	}
}

void Board::AddRooks() {
	board_[0][0] = new Rook(0, 0, Piece::Team::WHITE);
	board_[7][0] = new Rook(7, 0, Piece::Team::WHITE);
	board_[0][7] = new Rook(0, 7, Piece::Team::BLACK);
	board_[7][7] = new Rook(7, 7, Piece::Team::BLACK);
}

void Board::AddKnights() {
	board_[1][0] = new Knight(1, 0, Piece::Team::WHITE);
	board_[6][0] = new Knight(6, 0, Piece::Team::WHITE);
	board_[1][7] = new Knight(1, 7, Piece::Team::BLACK);
	board_[6][7] = new Knight(6, 7, Piece::Team::BLACK);
}

void Board::AddBishops() {
	board_[2][0] = new Bishop(2, 0, Piece::Team::WHITE);
	board_[5][0] = new Bishop(5, 0, Piece::Team::WHITE);
	board_[2][7] = new Bishop(2, 7, Piece::Team::BLACK);
	board_[5][7] = new Bishop(5, 7, Piece::Team::BLACK);
}

void Board::AddQueen() {
	board_[4][0] = new Queen(4, 0, Piece::Team::WHITE);
	board_[4][7] = new Queen(4, 7, Piece::Team::BLACK);
}

void Board::AddKing() {
	board_[3][0] = new King(3, 0, Piece::Team::WHITE);
	board_[3][7] = new King(3, 7, Piece::Team::BLACK);
}

bool Board::CanMove(int x, int y, const Piece* piece) const {
	auto spots = piece->GetPossibleMovementSpots(this);
	return std::find(spots.begin(), spots.end(), std::pair<int, int>(x, y)) != spots.end();
}