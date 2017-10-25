/*
 * SelectionRoulette.h
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#ifndef SELECTIONRANK_H_
#define SELECTIONRANK_H_

#include "SelectionOperator.h"

class SelectionRank: public SelectionOperator {
private:
    long totalRank;

public:
    SelectionRank();
    virtual ~SelectionRank();

	/**
	 * Funkcja przygotowuje klase do procesu selekcji.
	 * \param population referencja do wektora zawierajacego populacje chromosomow.
	 */
	void prepareSelection(vector<Chromosom> & population);

	/**
	 * Funkcja wybiera osobnika metoda ruletki.
	 * \return wybrany osobnik z populacji.
	 */
	Chromosom & selectParent();
};

#endif /* SELECTIONRANK_H_ */
