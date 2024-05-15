//
// Created by qwerty on 07.03.2024.
//

#ifndef DIPLOMA_MINIMAXH_H
#define DIPLOMA_MINIMAXH_H
#include "toguz.h"
#include "CONSTANTS.h"
#include <unordered_set>
#include <array>

struct MinimaxH{
    std::array<float, NUM_OF_HEURISTICS> weights{};
public:
    explicit MinimaxH(std::array<float, NUM_OF_HEURISTICS>& inputWeights);
    float minimaxWithABWithHeuristics(Board &board, int depth, float alpha, float beta, bool player, int &move, bool &tuzdek) const;
private:
    static int getNumOfLegalMoves(Board &board, bool p);
    static int getNumOfLegalMovesWithDistinctDestination(Board &board, bool p);
    float heuristic1(Board &board, bool p = false) const;
};

#endif //DIPLOMA_MINIMAXH_H
