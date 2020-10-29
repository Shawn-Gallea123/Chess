#include "Chess.h"

#include <iostream>
#include <memory>

#include "Board.h"
#include "Opponent.h"
#include "display/Display2D.h"
#include "display/TextDisplay.h"

Chess::Chess() : display_(std::make_unique<Display2D>()), board_(std::make_unique<Board>(Opponent::Difficulty::EASY, display_.get())) {
    display_->SetBoard(board_.get());
}

void Chess::Run() {
    while (true) {
        if (!display_->DrawBoard())
            break;
        if (board_->CheckForChecks(Piece::Team::WHITE))
            std::cout << "CHECK, white king must move." << std::endl;
        if (board_->CheckForChecks(Piece::Team::BLACK))
            std::cout << "CHECK, black king must move." << std::endl;
    }
}

void Chess::ChooseDifficulty() {
    std::cout << "Choose difficulty, 1-4: ";
    int difficulty = 1;
    //while (!(std::cin >> difficulty));
    opponent_ = std::make_unique<Opponent>(static_cast<Opponent::Difficulty>(difficulty - 1), board_.get());
}

bool Chess::WhiteTurn() {
    int x;
    int y;
    int dest_x;
    int dest_y;
    std::cout << "Enter" << std::endl;
    std::cin >> x;
    std::cin >> y;
    std::cin >> dest_x;
    std::cin >> dest_y;

    if (std::cin.fail())
        return false;

    board_->Move(x, y, dest_x, dest_y);
    return true;
}

void Chess::BlackTurn() {
    // TODO: Switch to boolean, add 2P/AI turn.
}