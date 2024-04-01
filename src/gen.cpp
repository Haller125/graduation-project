//
// Created by qwerty on 25.03.2024.
//

#include "gen_crossover.h"
#include "gen_mutation.h"
#include "gen_selection.h"
#include "gen_fitness.h"

#include <algorithm>
#include <execution>
#include <chrono>
#include <vector>
#include <thread>

static void initPopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        std::array<float, NUM_OF_HEURISTICS> individual;
        for (int j = 0; j < NUM_OF_HEURISTICS; j++) {
            individual[j] = static_cast<float>(rand() % 10000) / 10000;
        }
        population.push_back(individual);
    }
}


static void calcFitness(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness){
    std::vector<float> newFitness(POPULATION_SIZE);

    std::vector<std::thread> threads(POPULATION_SIZE);

    // Time taken: 2519 milliseconds
    for(int i = 0; i < POPULATION_SIZE; i++){
        threads[i] = std::thread([&, i](){
            newFitness[i] = gen_fitness(population[i]);
        });
    }

    for(auto& thread : threads){
        thread.join();
    }

//    Time taken: 47208 milliseconds
//    for(int i = 0; i < POPULATION_SIZE; i++){
//        newFitness.push_back(gen_fitness(population[i]));
//    }

    fitness = newFitness;

}

void geneticFunction(){
    srand(time(NULL));
    std::vector<std::array<float, NUM_OF_HEURISTICS>> population;
    std::vector<float> fitness;
    fitness.reserve(POPULATION_SIZE);

    initPopulation(population);

    std::cout << "Initial population are generated"  << std::endl;

    calcFitness(population, fitness);

    std::cout << "Fitnesses are generated"  << std::endl;

