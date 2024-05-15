//
// Created by qwerty on 06.03.2024.
//

#ifndef DIPLOMA_TOGUZ_H
#define DIPLOMA_TOGUZ_H

#include <iostream>
#include <array>
#include "CONSTANTS.h"
#include <iostream>
#include <limits>
#include <array>

struct Board{
public:
    std::array<int, K*2> sockets{};
    std::array<int, 2> tuzdeks{};
    std::array<int, 2> kaznas{};
    Board();
    Board(std::array<int, 2*K>& inSocket, std::array<int, 2>& inTuzdek, std::array<int, 2>& inKaznas);
    int getSumOfOtausOfPlayer(const int p);
    int getNumOfOddCells(const int p);
    int getNumOfEvenCells(const int p);
    float heurestic1(const int p);
    int playSocket(const int p);
    bool isMovePossible(const bool p);
    int atsyrauFunction(const int p);
    bool tuzdekPossible(const int s, const int player) const;
    void accountSocket(const int s, const size_t player);
    void pli(const int s, const bool tuzdek, const int player);
    Board rotate() const;
    static int idx(const int s);
};

std::ostream &operator<<(std::ostream &os, const Board &board);


int minimaxWithAB(Board &board, int depth, int alpha, int beta, bool player, int &move, bool &tuzdek);

#endif //DIPLOMA_TOGUZ_H
