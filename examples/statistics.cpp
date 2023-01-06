//
// Created by Carla on 20/06/2022.
//

#include "composer/optimizer.hpp"
#include "composer/genetic_algorithm.h"
#include "composer/nsga_ii.h"
#include "composer/statistics.h"

using namespace composer;

template <typename algorithm>
void solver() {

    // Parameters
    double crossover_strength = 0.8;
    double mutation_strength = 0.3;
    int population_size = 1000;
    size_t max_iterations = 30;
    size_t num_executions = 100;

    std::pair<double, double> target = {-1., 0.};
    const melody_problem p(melody_problem::problem_type::random, 100, target);

    for (size_t i = 0; i < num_executions; ++i) {
        optimizer<algorithm> ga(crossover_strength, mutation_strength, population_size, max_iterations, p);
        ga.optimize();
        ga.display();

        std::vector<melody> best_melodies;

        best_melodies = find_best_individuals(ga);

        for (const auto& m : best_melodies) {
            std::cout << m << std::endl;
        }
    }
}

int main() {

    solver<nsga_ii>();

    return 0;
}