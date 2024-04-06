//
// Created by qwerty on 25.03.2024.
//

#include "gen_mutation.h"

static std::mt19937 gen;

void setSeedForMutation(int seed) {
    gen.seed(seed); // Set the seed for the generator
}

double gaussianRandom(double mean, double stddev) {
    static std::normal_distribution<> dist(mean, stddev);
    return dist(gen);
}

void mutatePopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, float mutationRate) {
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (auto& individual : population) {
        for (float& gene : individual) {
            float randomNumber = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (randomNumber < mutationRate) {
                auto mutationValue = static_cast<float>(gaussianRandom(0.0, 1.0)); // Assuming gaussianRandom generates a value from a Gaussian distribution
                gene += mutationValue;
            }
            if (gene < -1.0) { gene = -1.0;} else if (gene > 1.0) { gene = 1.0; }
        }
    }
}
