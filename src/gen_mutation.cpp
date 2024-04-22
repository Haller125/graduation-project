//
// Created by qwerty on 25.03.2024.
//

#include "gen_mutation.h"


void mutatePopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, float mutationRate) {
    for (auto& individual : population) {
        for (float& gene : individual) {
            float randomNumber = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (randomNumber < mutationRate) {
                auto mutationValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Assuming gaussianRandom generates a value from a Gaussian distribution
                gene += mutationValue;
            }
            if (gene < -1.0) { gene = -1.0;} else if (gene > 1.0) { gene = 1.0; }
        }
    }
}
