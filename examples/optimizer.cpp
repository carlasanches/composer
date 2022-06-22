//
// Created by Carla on 20/06/2022.
//

#include "composer/optimizer.hpp"
#include "composer/genetic_algorithm.h"
#include "composer/nsga_ii.h"

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
    const melody_problem p(target, melody_problem::problem_type::twinkle);

    for (size_t i = 0; i < num_executions; ++i) {
        optimizer<algorithm> ga(crossover_strength, mutation_strength, population_size, max_iterations, p);
        ga.optimize();
        ga.display();
    }
}

int main() {

    solver<genetic_algorithm>();
    solver<nsga_ii>();

    return 0;
}