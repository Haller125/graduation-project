#include "gen.h"

int main() {
//    int seed = 1234;
//    geneticFunction(seed);
//
    Board board;
//    std::unique_ptr<IPlayer> player1 = std::make_unique<minimaxPlayer>(2);
//    std::unique_ptr<IPlayer> player2 = std::make_unique<humanPlayer>();
    std::unique_ptr<IPlayer> player4 = std::make_unique<minimaxPlayer>(8);
//
    std::array<float, NUM_OF_HEURISTICS> weights = {0.725848, 0.415992, 0.995413, -0.923265, -0.465954, -0.0554116, 0.301831, 0.725079, 0.170377};
    std::unique_ptr<IPlayer> player3 = std::make_unique<minimaxPlayerH>(weights, 4);
//
    Arena arena(std::move(player4), std::move(player3), board);
    arena.play();

//    float fitness = gen_fitness(weights);
//    std::cout << "Fitness: " << fitness << std::endl;

    return 0;
}
