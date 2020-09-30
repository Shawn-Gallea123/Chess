#pragma once

#include <string>
#include <vector>

class Board;

class Piece {
public:
	enum class Team {
		WHITE,
		BLACK,
	};

	Piece(int x, int y, Team team);
	~Piece();

	virtual char GetSymbol() = 0;
	virtual std::vector<std::pair<int, int>> GetPossibleMovementSpots(const Board* board, bool attacks_only) const = 0;
	Team GetTeam();
	virtual void OnMoved(int x, int y);
	int GetX();
	int GetY();

protected:
	bool CheckSpace(int x, int y, std::vector<std::pair<int, int>>& spots, const Board* board) const;

	int x_;
	int y_;
	Team team_;
};