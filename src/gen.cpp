//
// Created by qwerty on 25.03.2024.
//
#include "gen.h"

static void initPopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        std::array<float, NUM_OF_HEURISTICS> individual;
        for (int j = 0; j < NUM_OF_HEURISTICS; j++) {
            individual[j] = (static_cast<float>(rand() % 10000) / 10000) * (rand() % 2 == 0 ? 1 : -1);
        }
        population[i] = individual;
    }
}


void calcFitness(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness){
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
//          newFitness[i] = gen_fitness(population[i]);
//    }
//
    fitness = newFitness;

}

void crossoverPopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<std::array<float, NUM_OF_HEURISTICS>>& matingPool) {
    std::vector<std::array<float, NUM_OF_HEURISTICS>> newPopulation;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        std::array<float, NUM_OF_HEURISTICS> offspring1 = blxCrossover(matingPool[rand() % matingPool.size()], matingPool[rand() % matingPool.size()], 0.5f);
        newPopulation.push_back(offspring1);
    }

    population = newPopulation;
}

void saveProgress(const std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, const std::vector<float>& fitness, int generation) {
    std::ofstream file;
    file.open("progress_" + std::to_string(generation) + ".txt");

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (const auto& gene : population[i]) {
            file << gene << " ";
        }
        file << ": " << fitness[i] << "\n";
    }

    file.close();

    std::ofstream lastGenFile("last_gen.txt");
    lastGenFile << generation;
    lastGenFile.close();
}

void loadProgress(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness, int generation) {
    std::ifstream file;
    file.open("progress_" + std::to_string(generation) + ".txt");

    std::vector<std::array<float, NUM_OF_HEURISTICS>> newPopulation;
    std::vector<float> newFitness;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::array<float, NUM_OF_HEURISTICS> individual;
        for (auto& gene : individual) {
            iss >> gene;
        }
        newPopulation.push_back(individual);

        std::string fitnessStr;
        std::getline(iss, fitnessStr, ':');
        std::getline(iss, fitnessStr);
        newFitness.push_back(std::stof(fitnessStr));
    }

    population = newPopulation;
    fitness = newFitness;

    file.close();
}

void loadLastProgress(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness, int& generation) {
    // Read the number of the last generation
    std::ifstream lastGenFile("last_gen.txt");
    int lastGeneration;
    lastGenFile >> lastGeneration;
    lastGenFile.close();

    generation = lastGeneration + 1;

    std::cout << "Last generation: " << lastGeneration << std::endl;

    // Load the last generation
    loadProgress(population, fitness, lastGeneration);
}

void geneticFunction(int seed) {
    srand(seed);
    std::vector<std::array<float, NUM_OF_HEURISTICS>> population(POPULATION_SIZE);
    std::vector<float> fitness(POPULATION_SIZE);

    std::vector<std::array<float, NUM_OF_HEURISTICS>> matingPool;

    int i = 0;

    std::ifstream lastGenFile("last_gen.txt");
    if (lastGenFile.good()) {
        loadLastProgress(population, fitness, i);
        std::cout << "Last saved generation is loaded" << std::endl;
    } else {
        initPopulation(population);
        std::cout << "Initial population are generated" << std::endl;
    }
    lastGenFile.close();

    for (; i < 50; i++) {
        srand(seed);

        for (int j = 0; j < i; j++) {
            rand();
        }

        int subseed = rand();

        srand(subseed);

        calcFitness(population, fitness);
        alternisSelection(population, fitness, matingPool);
        saveProgress(population, fitness, i);
        crossoverPopulation(population, matingPool);
        mutatePopulation(population, 0.0125f);

        std::cout << "Generation " << i << " is completed" << std::endl;
    }
}
