//
// Created by qwerty on 08.03.2024.
//

#ifndef DIPLOMA_ARENA_H
#define DIPLOMA_ARENA_H
#include "agents.h"
#include <memory>
#include <iostream>
#include "toguz.h"

struct Arena {
    Arena(std::unique_ptr<IPlayer> player1, std::unique_ptr<IPlayer> player2, Board &board, bool isRotation = true);
    bool play();
private:
    std::unique_ptr<IPlayer> player1;
    std::unique_ptr<IPlayer> player2;
    Board board;
    bool isRotation = true;
    void logGameStatus(bool currentPlayer, int move, bool isGameFinished);
};

#endif //DIPLOMA_ARENA_H
