//
// Created by qwerty on 06.03.2024.
//

#include "agents.h"

minimaxPlayer::minimaxPlayer(int depth){
    this->depth = depth;
}

float minimaxPlayer::findMove(Board &board, bool player, int &move, bool &tuzdek){
    auto alpha = std::numeric_limits<int>::min(); // Negative infinity for an int
    auto beta = std::numeric_limits<int>::max(); // Positive infinity for an int
    int result = minimaxWithAB(board, this->depth, alpha, beta, player, move, tuzdek);
    return result;
}


minimaxPlayerH::minimaxPlayerH(std::array<float, NUM_OF_HEURISTICS> weights, int depth)
        : minimaxH(weights) {
    this->depth = depth;
}

float minimaxPlayerH::findMove(Board &board, bool player, int &move, bool &tuzdek){
    float alpha = std::numeric_limits<float>::min(); // Negative infinity for an int
    float beta = std::numeric_limits<float>::max(); // Positive infinity for an int
    float result = minimaxH.minimaxWithABWithHeuristics(board, this->depth, alpha, beta, player, move, tuzdek);
    return result;
}


