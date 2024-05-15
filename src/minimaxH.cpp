//
// Created by qwerty on 06.03.2024.
//


#include "minimaxH.h"

MinimaxH::MinimaxH(std::array<float, NUM_OF_HEURISTICS>& inputWeights) {
    weights = inputWeights;
}
float MinimaxH::minimaxWithABWithHeuristics(Board &board, int depth, float alpha, float beta, bool player, int &move, bool &tuzdek) const {
    if (depth == 0 || board.kaznas[0] > K * N || board.kaznas[1] > K * N) {
        move = -1;
        return this->heuristic1(board);
    }

    int dummyMove;
    bool dummyTuzdek;

    float bestValue = (player == 0) ? INT_MIN : INT_MAX;

    bool played = false;
    if (!board.isMovePossible(player)) {
        Board copyBoard(board);
        copyBoard.atsyrauFunction(!player);
        return board.kaznas[0] > K*K ? 10000000 : -1000000;
    }
    for (int i = player * K; i < player * K + K; ++i) {
        Board localBoard(board);
        if (localBoard.sockets[i] == 0) continue;
        played = true;
        auto target = localBoard.playSocket(i);
        bool isTuzdekPossible = localBoard.tuzdekPossible(target, player);

        float value = INT_MIN;
        if (isTuzdekPossible) {
            Board tuzdekBoard(localBoard);
            tuzdekBoard.tuzdeks[player] = target;
            tuzdekBoard.accountSocket(target, player);

            value = this->minimaxWithABWithHeuristics(tuzdekBoard, depth - 1, alpha, beta, 1 - player, dummyMove, dummyTuzdek);
        }else {
            localBoard.accountSocket(target, player);
            value = this->minimaxWithABWithHeuristics(localBoard, depth - 1, alpha, beta, 1 - player, dummyMove, dummyTuzdek);
        }
        if (player == 0 && value > bestValue) {  // Maximizing player
            bestValue = value;
            move = i;
            tuzdek = isTuzdekPossible;
            alpha = std::max(alpha, bestValue);
        } else if (player == 1 && value < bestValue) {  // Minimizing player
            bestValue = value;
            move = i;
            tuzdek = isTuzdekPossible;
            beta = std::min(beta, bestValue);
        }
        if (beta <= alpha) break;
    }

    if (played) {
        return bestValue;
    } else {
        move = -1;
        return (float)board.kaznas[0];
    }
}

int MinimaxH::getNumOfLegalMoves(Board &board, const bool p){
    int result = 0;
    for (int i = p * K; i < K * (1 + p); ++i) {
        if (board.sockets[i]) {
            int a = board.sockets[i] / (2*K);
            int b = board.sockets[i] % (2*K);
            int c = board.sockets[b] + a;
            if ((c == 3) && (b / K == (1 - p)) &&   // opposite side
            (((b + 1) % K) != 0) &&                 // not the last
            (board.tuzdeks[p] == -1) &&             // not having tuzdek
            (board.tuzdeks[1 - p] == -1 || board.tuzdeks[1 - p] % K != b % K))  // not symmetrical tuzdek
            {
                result++;
            }
            result++;
        }
    }
    return result;
}
int MinimaxH::getNumOfLegalMovesWithDistinctDestination(Board &board, bool p){
    int result = 0;
    std::unordered_set<int> destinations = {};
    for (int i = p * K; i < K * (1 + p); ++i) {
        if (board.sockets[i])
        {
            int a = board.sockets[i] / (2*K);
            int b = board.sockets[i] % (2*K);
            int c = board.sockets[b] + a;
            if (destinations.count(b) <= 0){
                destinations.insert(b);
            }
            if (destinations.count(-b) <= 0 &&
                ((c == 3) && (b / K == (1 - p)) &&      // opposite side
                (((b + 1) % K) != 0) &&                 // not the last
                (board.tuzdeks[p] == -1) &&             // not having tuzdek
                (board.tuzdeks[1 - p] == -1 || board.tuzdeks[1 - p] % K != b % K)))  // not symmetrical tuzdek
            {
                destinations.insert(-b);
            }
        }
    }
    result = destinations.size();
    return result;
}
float MinimaxH::heuristic1(Board &board, bool p) const {
    return (board.kaznas[p]) * weights[0] +
           (board.getSumOfOtausOfPlayer(p)) * weights[1] +
           (board.tuzdeks[p]) * weights[2] +
           (board.tuzdeks[1-p]) * weights[3] +
           (board.getNumOfOddCells(1-p)) * weights[4] +
           (board.getNumOfEvenCells(p)) * weights[5] +
           (this->getNumOfLegalMoves(board,p)) * weights[6] +
           (this->getNumOfLegalMovesWithDistinctDestination(board, p)) * weights[7];
}
