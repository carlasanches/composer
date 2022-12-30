#include "statistics.h"
#include "optimizer.hpp"

namespace composer {
    std::vector<melody> find_best_individuals(optimizer<nsga_ii>& ga) {

        std::vector<melody> best_individuals;

        std::vector<std::vector<double>> emotions = {
            {0.,1.,0.,0.},     // Pleasure
            {0.,0.7,0.,0.7},   // Excitement
            {0.,0.,0.,1.},     // Arousal
            {-0.7,0.,0.,0.7},  // Distress
            {-1.,0.,0.,0.},    // Misery
            {-0.7,0.,-0.7,0.}, // Depression
            {0.,0.,-1.,0.},    // Sleepiness
            {0.,0.7,-0.7,0.}   // Contentment
        };

        for (const auto& emotion : emotions) {
            best_individuals.emplace_back(
                ga.get_solver().get_population().find_nearest({ emotion[0], emotion[1], emotion[2], emotion[3] })->second
            );
        }

        return best_individuals;
    }
}