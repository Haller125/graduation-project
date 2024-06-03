#include "gen.h"

int main() {
//    int seed = 1234;
//    geneticFunction(seed);

    Board board;
//    std::unique_ptr<IPlayer> player1 = std::make_unique<minimaxPlayer>(10);
//    std::unique_ptr<IPlayer> player2 = std::make_unique<humanPlayer>();
//    std::unique_ptr<IPlayer> player4 = std::make_unique<minimaxPlayer>(4);
//
    std::array<float, NUM_OF_HEURISTICS> weights = {0.725848, 0.415992, 0.995413, -0.923265, -0.465954, -0.0554116, 0.301831, 0.725079, 0.170377};
    std::unique_ptr<IPlayer> player3 = std::make_unique<minimaxPlayerH>(weights, 4);
//
//    Arena arena(std::move(player3), std::move(player1), board);
//    arena.play();

//    float fitness = gen_fitness(weights);
//    std::cout << "Fitness: " << fitness << std::endl;

    int a;
    bool b;

    auto start = std::chrono::high_resolution_clock::now();

    player3->findMove(board, 0, a, b);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    //758,234 milliseconds
    //3,017 milliseconds


    return 0;
}
