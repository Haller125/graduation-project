//
// Created by qwerty on 24.03.2024.
//

#include "gen_crossover.h"

std::array<float, NUM_OF_HEURISTICS> blxCrossover(
        const std::array<float, NUM_OF_HEURISTICS>& parent1,
        const std::array<float, NUM_OF_HEURISTICS>& parent2,
        float alpha) {

    std::array<float, NUM_OF_HEURISTICS> offspring;

    for (int i = 0; i < NUM_OF_HEURISTICS; i++) {
        float minGeneValue = std::min(parent1[i], parent2[i]);
        float maxGeneValue = std::max(parent1[i], parent2[i]);
        float range = maxGeneValue - minGeneValue;

        float minRange = minGeneValue - range * alpha;
        float maxRange = maxGeneValue + range * alpha;

        float geneValue = minRange + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxRange - minRange);
        offspring[i] = geneValue;
    }

    return offspring;
}