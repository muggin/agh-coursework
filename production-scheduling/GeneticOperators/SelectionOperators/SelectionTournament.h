/*
 * SelectionTournament.h
 *
 *  Created on: May 1, 2014
 *      Author: Wojtek
 */

#ifndef SELECTIONTOURNAMENT_H_
#define SELECTIONTOURNAMENT_H_
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>

#include "SelectionOperator.h"

class SelectionTournament: public SelectionOperator {
private:
	int competitorCount;
	double selectionProbability;

public:
    SelectionTournament(double selectionProbability = 0.8, int competitorCount = 5);
	virtual ~SelectionTournament();

	/**
	 * Funkcja przygotowuje klase do procesu selekcji.
	 * \param population referencja do wektora zawierajacego populacje chromosomow.
	 */
	void prepareSelection(vector<Chromosom> & population);

	/**
	 * Funkcja wybiera osobnika metoda turniejowa.
	 * \return wybrany osobnik z populacji.
	 */
	Chromosom & selectParent();
};

#endif /* SELECTIONTOURNAMENT_H_ */
