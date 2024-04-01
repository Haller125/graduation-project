//
// Created by qwerty on 08.03.2024.
//

#include "agents.h"
#include <iostream>
#include "toguz.h"
#include "arena.h"

bool logging = false;


Arena::Arena(IPlayer* player1, IPlayer* player2, Board& board)
        : player1(player1), player2(player2), board(board){};

bool Arena::play(){
    bool atsyrau[2] {false, false};
    bool currentPlayer = false;
    bool isGameFinished = false;
    while (true){
        int move; bool tuzdek;
        if (isGameFinished) {

            return board.kaznas[0] >= 81;
        }
        if (atsyrau[currentPlayer] && !board.isMovePossible(currentPlayer)) {
            board.atsyrauFunction(currentPlayer);
            isGameFinished = true;
            continue;
        }
        if (!board.isMovePossible(currentPlayer)){
            atsyrau[currentPlayer] = true;
            currentPlayer = !currentPlayer;
            continue;
        }
        if (!currentPlayer){
            float result = player1->findMove(board, currentPlayer, move, tuzdek);
        }
        else{
            float result = player2->findMove(board, currentPlayer, move, tuzdek);
        }
        board.pli(move, tuzdek, currentPlayer);
        if (board.kaznas[0] >= 81 || board.kaznas[1] > 81) { isGameFinished = true; }
        atsyrau[currentPlayer] = false;
        currentPlayer = !currentPlayer;

        if (logging) {logGameStatus(currentPlayer, move, tuzdek, isGameFinished);}
    }
}

void Arena::logGameStatus(bool currentPlayer, int move, bool tuzdek, bool isGameFinished) {
    std::cout << board.rotate() << std::endl;
    std::cout << "Player " << currentPlayer << "\tmade a move: " << move << "\twith tuzdek " << tuzdek << std::endl;
    std::cout << "Is game finished? " << isGameFinished << std::endl;
    if (isGameFinished){
        std::cout << "And it is done! Someone prevailed with honor, while other fall in shame" << std::endl;
    }
}

