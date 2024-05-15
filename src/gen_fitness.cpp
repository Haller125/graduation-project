//
// Created by qwerty on 13.03.2024.
//
#include "gen_fitness.h"


float gen_fitness(std::array<float, NUM_OF_HEURISTICS>& weights) {
    short wins = 0;

    for (int i = 0; i < NUM_OF_GAMES; i++) {
        bool winner;
        Board newboard;
        int depthForRegMinMax = (rand() % 4) + 5;
        int depthForHMinMax = (rand() % 3) + 3;
        std::unique_ptr<IPlayer> player1 = std::make_unique<minimaxPlayer>(depthForRegMinMax);
        std::unique_ptr<IPlayer> player2 = std::make_unique<minimaxPlayerH>(weights, depthForHMinMax);
        int coin = rand() % 2;
        if (coin){
            Arena arena(std::move(player1), std::move(player2), newboard);
            winner = !arena.play();
        }
        else {
            Arena arena(std::move(player2), std::move(player1), newboard);
            winner = arena.play();
        }
        wins += winner;
    }
    return static_cast<float>(wins)/NUM_OF_GAMES;
}