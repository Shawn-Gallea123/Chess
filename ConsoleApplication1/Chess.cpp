#include "Chess.h"

#include <iostream>
#include <memory>

#include "Board.h"
#include "Opponent.h"

Chess::Chess() : board_(std::make_unique<Board>()) {}

void Chess::Run() {
    board_->PrintBoard();

    ChooseDifficulty();

    while (true) {
        if (!WhiteTurn())
            break;
        board_->PrintBoard();
        CheckForChecks();
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

void Chess::CheckForChecks() {

}