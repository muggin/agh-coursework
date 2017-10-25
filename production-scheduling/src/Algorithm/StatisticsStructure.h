#ifndef STATISTICSSTRUCTURE_H
#define STATISTICSSTRUCTURE_H

#include <vector>
using namespace std;

struct AlgorithmStatistics {
    int lastImprovement;    //!< Ilość epok od wyboru najlepszego chromosomu.
    int sameParents;    //!< Ilość wyboru takich samych rodziców do krzyżowania.
    int mutationCount;  //!< Ilość przeprowadzonych mutacji.
    int crossoverCount; //!< Ilość przeprowadzonych krzyżowań.
    int invalidSolutions;   //!< Ilość niepoprawnych chromosomów powstałych po krzyżowaniu.

    vector<double> epoch;  //!< Numer aktualnej epoki.
    vector<double> bestFitness;    //!< Struktura przechowująca wartości fitness najlepszego osobnika.
    vector<double> populationFitness;   //!< Struktura przechowująca wartości fitness populacji.

    void clearStatistics() {
        lastImprovement = 0;
        sameParents = 0;
        mutationCount = 0;
        crossoverCount = 0;
        invalidSolutions = 0;
        epoch.clear();
        bestFitness.clear();
        populationFitness.clear();
    }

};


#endif // STATISTICSSTRUCTURE_H
