//
// Created by qwerty on 25.03.2024.
//

#ifndef DIPLOMA_GEN_CROSSOVER_H
#define DIPLOMA_GEN_CROSSOVER_H

#include <array>
#include <cstdlib>
#include "CONSTANTS.h"
#include <ctime>

std::array<float, NUM_OF_HEURISTICS> blxCrossover(
        const std::array<float, NUM_OF_HEURISTICS>& parent1,
        const std::array<float, NUM_OF_HEURISTICS>& parent2,
        float alpha);

#endif //DIPLOMA_GEN_CROSSOVER_H
