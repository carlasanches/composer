#ifndef COMPOSER_STATISTICS_H
#define COMPOSER_STATISTICS_H

#include "nsga_ii.h"
#include "optimizer.h"

namespace composer {

	std::vector<melody> find_best_individuals(optimizer<nsga_ii>& ga);
}

#endif // !COMPOSER_STATISTICS_H
