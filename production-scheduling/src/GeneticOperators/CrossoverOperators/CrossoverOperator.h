/*
 * CrossoverOperator.h
 *
 *  Created on: May 1, 2014
 *      Author: Wojtek
 */

#ifndef CROSSOVEROPERATOR_H_
#define CROSSOVEROPERATOR_H_
#include "../../Algorithm/Chromosom.h"

class CrossoverOperator {
public:
	CrossoverOperator();
	virtual ~CrossoverOperator();

	/**
	 * Funkcja dokonuje krzyzowania.
	 * \param parentA pierwszy osobnik pelniacy role rodzica.
	 * \param parentB drugi osobnik pelniacy role rodzica.
	 * \param childA pierwszy osobnik pelniacy role dziecka.
	 * \param childB drugi osobnik pelniacy role dziecka.
	 */
	virtual void crossChromosoms(const Chromosom & parentA, const Chromosom & parentB, Chromosom & childA, Chromosom & childB) = 0;

    void identifyObject();
};

#endif /* CROSSOVEROPERATOR_H_ */
