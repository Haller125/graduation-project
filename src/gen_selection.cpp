//
// Created by qwerty on 22.03.2024.
//

#include "gen_selection.h"

void tournamentSelection(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness) {
    std::vector<std::array<float, NUM_OF_HEURISTICS>> newPopulation;
    std::vector<float> newFitness;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        int first = rand() % POPULATION_SIZE;
        int second = rand() % POPULATION_SIZE;
        if (fitness[first] > fitness[second]) {
            newPopulation.push_back(population[first]);
            newFitness.push_back(fitness[first]);
        } else {
            newPopulation.push_back(population[second]);
            newFitness.push_back(fitness[second]);
        }
    }
    population = newPopulation;
    fitness = newFitness;
}