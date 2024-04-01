//
// Created by qwerty on 08.03.2024.
//

#ifndef DIPLOMA_AGENTS_H
#define DIPLOMA_AGENTS_H

#include "toguz.h"
#include "minimaxH.h"
#include <limits>
#include <string>
#include <utility>

struct IPlayer {
    virtual ~IPlayer() = default;
    virtual float findMove(Board &board, bool player, int &move, bool &tuzdek) = 0;
};

struct minimaxPlayer : public IPlayer {
    int depth;
public:
    minimaxPlayer(int depth);
    float findMove(Board &board, bool player, int &move, bool &tuzdek) override;
};

struct minimaxPlayerH : public IPlayer {
    int depth;
    std::string name;
public:
    minimaxPlayerH(std::array<float, NUM_OF_HEURISTICS> weights, int depth);
    float findMove(Board &board, bool player, int &move, bool &tuzdek) override;
private:
    MinimaxH minimaxH;
};

#endif //DIPLOMA_AGENTS_H
