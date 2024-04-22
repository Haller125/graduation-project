//
// Created by qwerty on 25.03.2024.
//

#ifndef DIPLOMA_GEN_MUTATION_H
#define DIPLOMA_GEN_MUTATION_H

#include <array>
#include <vector>
#include <cstdlib>
#include "CONSTANTS.h"
#include <random>

void mutatePopulation(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, float mutationRate);

#endif //DIPLOMA_GEN_MUTATION_H
