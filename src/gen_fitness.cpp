//
// Created by qwerty on 13.03.2024.
//
#include "gen_fitness.h"


float gen_fitness(std::array<float, NUM_OF_HEURISTICS>& weights) {
    short wins = 0;

    srand ( time(NULL) );
    for (int i = 0; i < NUM_OF_GAMES; i++) {
        bool winner;
        Board newboard;
        int depthForRegMinMax = (rand() % 4) + 5 ;
        int depthForHMinMax = (rand() % 3) + 3;
        IPlayer* player1 = new minimaxPlayer(depthForRegMinMax);
        IPlayer* player2 = new minimaxPlayerH(weights, depthForHMinMax);
        int coin = rand() % 2;
        if (coin){
            Arena arena(player1, player2, newboard);
            winner = !arena.play();
        }
        else {
            Arena arena(player2, player1, newboard);
            winner = arena.play();
        }
        wins += winner;
    }
    return static_cast<float>(wins)/NUM_OF_GAMES;
}