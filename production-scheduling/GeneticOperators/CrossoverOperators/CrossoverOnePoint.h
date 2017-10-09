/*
 * CrossoverOnePoint.h
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#ifndef CROSSOVERONEPOINT_H_
#define CROSSOVERONEPOINT_H_

#include "CrossoverOperator.h"

class CrossoverOnePoint: public CrossoverOperator {
public:
	CrossoverOnePoint();
	virtual ~CrossoverOnePoint();

	/**
	 * Funkcja dokonuje krzyzowania metoda jednopunktowa.
	 * \param parentA pierwszy osobnik pelniacy role rodzica.
	 * \param parentB drugi osobnik pelniacy role rodzica.
	 * \param childA pierwszy osobnik pelniacy role dziecka.
	 * \param childB drugi osobnik pelniacy role dziecka.
	 */
	void crossChromosoms(const Chromosom & parentA, const Chromosom & parentB, Chromosom & childA, Chromosom & childB);
};

#endif /* CROSSOVERONEPOINT_H_ */
