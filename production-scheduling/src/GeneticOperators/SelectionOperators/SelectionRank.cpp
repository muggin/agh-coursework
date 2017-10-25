/*
 * SelectionRoulette.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#include "SelectionRank.h"

SelectionRank::SelectionRank() {
    this->totalRank = 0;
}

SelectionRank::~SelectionRank() {
	// TODO Auto-generated destructor stub
}

void SelectionRank::prepareSelection(vector<Chromosom> & population) {
    size_t populationSize = population.size();
    this->population = population;
    totalRank = populationSize * ((1 + populationSize) / 2);
}

Chromosom & SelectionRank::selectParent() {
    int combinedRank = 0;
    double randomProbability = (double)rand() / RAND_MAX;

    size_t index, currentRank;
    for (index = 0, currentRank = population.size(); index < population.size(); index++, currentRank--) {
        combinedRank += currentRank;
        if (((double)combinedRank / totalRank) > randomProbability)
            return population[index];
    }
    return *population.end();
}

