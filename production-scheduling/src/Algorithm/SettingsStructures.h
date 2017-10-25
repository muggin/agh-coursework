#ifndef SETTINGSSTRUCTURES_H_
#define SETTINGSSTRUCTURES_H_
#include "../GeneticOperators/SelectionOperators/SelectionOperator.h"
#include "../GeneticOperators/MutationOperators/MutationOperator.h"
#include "../GeneticOperators/CrossoverOperators/CrossoverOperator.h"

struct AlgorithmSettings {
	int maxEpochs;	//!< Maksymalna liczba epok;
	int maxEpochsWithoutChange;	//!< Maksymalna liczba epok bez zmiany najlepszego osobnika.
	int populationSize;	//!< Rozmiar populacji.
	int newPopulationSize;	//!< Rozmiar populacji powstalej z krzyzowania.
    bool repairChromosom;   //!< Flaga czy algorytm ma próbować naprawiać niepoprawne chromosomy.
	double mutationProbability;	//!< Prawdopodobienstwo mutacji osobnika.
	double crossoverProbability;	//!< Prawdopodobienstwo krzyzowania.

    SelectionOperator * selectionOperator;	//!< Wskaznik do klasy pelniacej funkcje operatora selekcji.
    MutationOperator * mutationOperator;	//!< Wskaznik do klasy pelniacej funkcje operatora mutacji.
    CrossoverOperator * crossoverOperator;	//!< Wskaznik do klasy pelniacej funkcje operatora krzyzowania.

	//SettingsAlgorithm(int maxEpochs, int maxEpochsWithoutChange, int populationSize, int newPopulationSize, int mutationProability, int crossoverProbability);
	//~SettingsAlgorithm();
};

#endif /* SettingsStructures.h */
