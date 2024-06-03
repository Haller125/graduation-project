import pandas as pd
import matplotlib.pyplot as plt
import os
import re


def calculate_average_fitness(file):
    df = pd.read_csv(file, sep=" ", header=None)
    average_fitness = df.iloc[:, -1].mean()  # assuming fitness is the last column
    return average_fitness


def calculate_max_fitness(file):
    df = pd.read_csv(file, sep=" ", header=None)
    max_fitness = df.iloc[:, -1].max()
    return max_fitness


def extract_number(file):
    match = re.search(r'\d+', file)
    return int(match.group()) if match else None


directory1 = "wrong-cases/convergence-to-zero/"
directory2 = "wrong-cases/tournament+alternis/"
directory3 = "good-cases/tournament-selection/"
directory4 = "cmake-build-debug/"

directory = directory2

files = os.listdir(directory)

progress_files = [directory + file for file in files if 'progress' in file]
progress_files = sorted(progress_files, key=extract_number)

average_fitnesses = [calculate_average_fitness(file) for file in progress_files]
max_fitnesses = [calculate_max_fitness(file) for file in progress_files]

breakpoint1 = 24
average_fitnesses_before = average_fitnesses[:breakpoint1+1]
average_fitnesses_from = average_fitnesses[breakpoint1:]

breakpoint2 = 24
max_fitnesses_before = max_fitnesses[:breakpoint2+1]
max_fitnesses_from = max_fitnesses[breakpoint2:]

# plt.plot(average_fitnesses)

# plt.plot(average_fitnesses_before, color='blue', label='Tournament')
# plt.plot(range(24, len(average_fitnesses)), average_fitnesses_from, color='red', label='Alternis')
# plt.legend()

plt.plot(max_fitnesses_before, color='blue', label='Tournament')
plt.plot(range(24, len(average_fitnesses)), max_fitnesses_from, color='red', label='Alternis')
plt.legend()

plt.ylim(0, 1)
plt.xlabel('Generation')
plt.ylabel('Max Fitness')
plt.title('Max Fitness of Each Generation')
plt.savefig((directory + 'plotMaxC.svg'), format='svg')
plt.show()

