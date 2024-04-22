//
// Created by qwerty on 25.03.2024.
//
#include "gen.h"

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

void crossoverPopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population) {
    std::vector<std::array<float, NUM_OF_HEURISTICS>> newPopulation;

    for (int i = 0; i < population.size(); i += 2) {
        std::array<float, NUM_OF_HEURISTICS> offspring1 = blxCrossover(population[i], population[i+1], 0.5f);
        std::array<float, NUM_OF_HEURISTICS> offspring2 = blxCrossover(population[i], population[i+1], 0.5f);
        newPopulation.push_back(offspring1);
        newPopulation.push_back(offspring2);
    }

    population = newPopulation;
}

void saveProgress(const std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, const std::vector<float>& fitness, int generation) {
    std::ofstream file;
    file.open("progress_" + std::to_string(generation) + ".txt");

    for (int i = 0; i < population.size(); i++) {
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

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::array<float, NUM_OF_HEURISTICS> individual;
        for (auto& gene : individual) {
            iss >> gene;
        }
        population.push_back(individual);

        std::string fitnessStr;
        std::getline(iss, fitnessStr, ':');
        std::getline(iss, fitnessStr);
        fitness.push_back(std::stof(fitnessStr));
    }

    file.close();
}

void loadLastProgress(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness, int& generation) {
    // Read the number of the last generation
    std::ifstream lastGenFile("last_gen.txt");
    int lastGeneration;
    lastGenFile >> lastGeneration;
    lastGenFile.close();

    generation = lastGeneration;

    // Load the last generation
    loadProgress(population, fitness, lastGeneration);
}

void geneticFunction(int seed) {
    srand(seed);
    std::vector<std::array<float, NUM_OF_HEURISTICS>> population;
    std::vector<float> fitness;
    fitness.reserve(POPULATION_SIZE);
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

    for (; i < 100; i++) {
        srand(12345);

        for (int j = 0; j < i; j++) {
            rand();
        }

        int subseed = rand();

        srand(subseed%1000);

        calcFitness(population, fitness);
        tournamentSelection(population, fitness);
        crossoverPopulation(population);
        mutatePopulation(population, 0.01f);
        saveProgress(population, fitness, i); // Save progress at the end of each generation
    }
}
