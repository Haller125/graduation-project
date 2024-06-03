//
// Created by qwerty on 08.03.2024.
//


#include "arena.h"

Arena::Arena(std::unique_ptr<IPlayer> player1, std::unique_ptr<IPlayer> player2, Board &board, bool isRotation)
        : player1(std::move(player1)), player2(std::move(player2)), board(board) {
    this->isRotation = isRotation;
};

bool Arena::play(){
    bool atsyrau[2] {false, false};
    bool currentPlayer = false;
    bool isGameFinished = false;
    while (true){
        int move; bool tuzdek;
        if (isGameFinished) {
            return board.kaznas[0] >= K*K;
        }
        if (!board.isMovePossible(currentPlayer)) {
            board.atsyrauFunction(!currentPlayer);
            isGameFinished = true;
            continue;
        }
        if (!currentPlayer){
            float result = player1->findMove(board, currentPlayer, move, tuzdek);
        }
        else{
            float result = player2->findMove(board, currentPlayer, move, tuzdek);
        }
        board.pli(move, tuzdek, currentPlayer);
        if (board.kaznas[0] >= K*K || board.kaznas[1] > K*K) {
            isGameFinished = true;
        }
        currentPlayer = !currentPlayer;

        if (LOGGING) {logGameStatus(currentPlayer, move, isGameFinished);}
    }
}

void Arena::logGameStatus(bool currentPlayer, int move, bool isGameFinished) {
    std::cout << (this->isRotation ? board.rotate() : board) << std::endl;
    std::cout << "Player " << currentPlayer + 1 << "\tmade a move: " << (move % K) + 1 << std::endl;
    std::cout << "Is game finished? " << isGameFinished << std::endl;
    if (isGameFinished){
        std::cout << "And it is done! Someone prevailed with honor, while other fall in shame" << std::endl;
    }
}

