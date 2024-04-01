//
// Created by qwerty on 25.03.2024.
//

#ifndef DIPLOMA_GEN_SELECTION_H
#define DIPLOMA_GEN_SELECTION_H

#include "CONSTANTS.h"
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>

void tournamentSelection(std::vector<std::array<float, NUM_OF_HEURISTICS>>& population, std::vector<float>& fitness);

#endif //DIPLOMA_GEN_SELECTION_H
