#include "TextDisplay.h"

#include <iostream>

#include "../Board.h"

bool TextDisplay::DrawBoard() {
	for (int i = 0; i < 16; ++i)
		std::cout << '-';
	std::cout << std::endl;
	for (int y = 7; y >= 0; --y)
		for (int x = 0; x < 8; ++x) {
			if (x == 0)
				std::cout << '|';

			if (board_->GetPiece(x, y))
				std::cout << board_->GetPiece(x, y)->GetSymbol();
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
	return true;
}