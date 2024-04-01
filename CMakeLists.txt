cmake_minimum_required(VERSION 3.25)
project(diploma)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(diploma src/main.cpp src/toguz.cpp src/minimaxH.cpp src/agents.cpp src/arena.cpp src/gen_fitness.cpp src/gen_selection.cpp src/gen_crossover.cpp src/gen_mutation.cpp src/gen.cpp)
