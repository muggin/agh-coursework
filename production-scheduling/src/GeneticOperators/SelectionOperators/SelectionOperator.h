/*
 * SelectionOperator.h
 *
 *  Created on: May 1, 2014
 *      Author: Wojtek
 */

#ifndef SELECTIONOPERATOR_H_
#define SELECTIONOPERATOR_H_
#include <vector>
#include "../../Algorithm/Chromosom.h"

class SelectionOperator {
protected:
	vector<Chromosom> population;	//!< wektor przechowujacy aktualna populacje chromosomow.
public:

	SelectionOperator();
	virtual ~SelectionOperator();

	/**
	 * Funkcja przygotowuje klase do procesu selekcji.
	 * \param population referencja do wektora zawierajacego populacje chromosomow.
	 */
	virtual void prepareSelection(vector<Chromosom> & population) = 0;

	/**
	 * Funkcja wybiera osobnika.
	 * \return wybrany osobnik z populacji.
	 */
	virtual Chromosom & selectParent() = 0;

    void identifyObject();
};

#endif /* SELECTIONOPERATOR_H_ */
