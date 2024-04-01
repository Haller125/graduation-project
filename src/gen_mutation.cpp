//
// Created by qwerty on 25.03.2024.
//

#include "gen_mutation.h"

double gaussianRandom(double mean, double stddev) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> dist(mean, stddev);

    return dist(gen);
}

void mutatePopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, float mutationRate) {
    for (auto& individual : population) {
        for (float& gene : individual) {
            float randomNumber = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (randomNumber < mutationRate) {
                float mutationValue = static_cast<float>(gaussianRandom(0.0, 1.0)); // Assuming gaussianRandom generates a value from a Gaussian distribution
                gene += mutationValue;
            }
        }
    }
}
