//
// Created by qwerty on 08.03.2024.
//

#ifndef DIPLOMA_ARENA_H
#define DIPLOMA_ARENA_H
#include "agents.h"
#include <memory>

struct Arena {
    Arena(IPlayer *player1, IPlayer *player2, Board &board);
    bool play();
private:
    std::unique_ptr<IPlayer> player1;
    std::unique_ptr<IPlayer> player2;
    Board board;
    void logGameStatus(bool currentPlayer, int move, bool tuzdek, bool isGameFinished);
};

#endif //DIPLOMA_ARENA_H
