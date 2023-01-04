#ifndef COMPOSER_STATISTICS_H
#define COMPOSER_STATISTICS_H

#include "nsga_ii.h"
#include "optimizer.h"

/// \file statistics.h
/// @brief Optimization process statistics.
/// 
/// This library contains functions to calculate the best individuals of the Pareto front.
namespace composer {

	/// @brief Calculates the individuals that are closer to the objectives of the problem.
	/// @param ga The genetic algorithm that solves the problem.
	/// @return The individuals closest to the objectives of the problem.
	///	They represent emotions in the Circumplex Model.
	std::vector<melody> find_best_individuals(optimizer<nsga_ii>& ga);
}

#endif // !COMPOSER_STATISTICS_H
