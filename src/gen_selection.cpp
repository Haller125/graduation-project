//
// Created by qwerty on 22.03.2024.
//

#include "gen_selection.h"

void tournamentSelection(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population,
                         std::vector<float>& fitness,
                         std::vector<std::array<float, NUM_OF_HEURISTICS>>& matingPool) {
    std::vector<std::array<float, NUM_OF_HEURISTICS>> newPopulation;
    std::vector<float> newFitness;
    std::vector<std::array<float, NUM_OF_HEURISTICS>> newMatingPool(MATING_POOL_SIZE);

    for (int i = 0; i < MATING_POOL_SIZE; i++) {
        int first = rand() % POPULATION_SIZE;
        int second = rand() % POPULATION_SIZE;
        if (fitness[first] > fitness[second]) {
            newMatingPool[i] = population[first];
        } else {
            newMatingPool[i] = population[second];
        }
    }
    matingPool = newMatingPool;
}

void alternisSelection (std::vector<std::array<float, NUM_OF_HEURISTICS>>& population,
                        std::vector<float>& fitness,
                        std::vector<std::array<float, NUM_OF_HEURISTICS>>& matingPool) {
    std::vector<int> indices(POPULATION_SIZE);
    std::iota(indices.begin(), indices.end(), 0);

    // Sort indices by ascending fitness
    std::sort(indices.begin(), indices.end(),
              [&](int a, int b) { return fitness[a] < fitness[b]; });

    int j = 0;
    int indicesSize = indices.size();

    std::vector<int> tempIndices(indicesSize);

    // Arrange individuals in alternating fashion: worst, best, 2nd worst, 2nd best, etc.
    for (int i = 0; i < indicesSize / 2; ++i) {
        tempIndices[2 * i] = indices[i]; // worst
        tempIndices[2 * i + 1] = indices[indicesSize - 1 - i]; // best
    }
    if (indicesSize % 2 != 0) {
        tempIndices[indicesSize - 1] = indices[indicesSize / 2];
    }

    indices = tempIndices;

    int N = population.size();
    int X = MATING_POOL_SIZE;
    int leftRange, rightRange;

    if (X % 2 == 0) {
        leftRange = X / 2;
        rightRange = X / 2;
    } else {
        leftRange = (X - 1) / 2;
        rightRange = (X + 1) / 2;
    }

    int start = rand() % (N - X + 1); // Random starting point within the defined range

    // Clear the mating pool and reserve space
    matingPool.clear();
    matingPool.reserve(X);

    // Select individuals for the mating pool in an alternating fashion
    for (int i = 0; i <= leftRange; ++i) {
        matingPool.push_back(population[indices[start + i]]); // from the left side (worst fit)
        matingPool.push_back(population[indices[start + X - 1 - i]]); // from the right side (best fit)
    }

    if (X % 2 != 0) {
        matingPool.push_back(population[indices[start + leftRange]]); // Middle element if X is odd
    }
}
