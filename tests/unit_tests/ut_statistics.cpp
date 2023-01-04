#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "composer/statistics.h"
#include "composer/optimizer.hpp"

using namespace composer;

TEST_CASE("Best individuals in an empty population") {

	melody_problem p(melody_problem::problem_type::twinkle);
	optimizer<nsga_ii> ga(0.3, 0.1, 100, 100, p);

	REQUIRE_FALSE(find_best_individuals(ga).empty());
}