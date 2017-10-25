/*
 * CrossoverTwoPoint.h
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#ifndef CROSSOVERTWOPOINT_H_
#define CROSSOVERTWOPOINT_H_

#include "CrossoverOperator.h"

class CrossoverTwoPoint: public CrossoverOperator {
public:
	CrossoverTwoPoint();
	virtual ~CrossoverTwoPoint();

	/**
	 * Funkcja dokonuje krzyzowania metoda dwupunktowa.
	 * \param parentA pierwszy osobnik pelniacy role rodzica.
	 * \param parentB drugi osobnik pelniacy role rodzica.
	 * \param childA pierwszy osobnik pelniacy role dziecka.
	 * \param childB drugi osobnik pelniacy role dziecka.
	 */
	void crossChromosoms(const Chromosom & parentA, const Chromosom & parentB, Chromosom & childA, Chromosom & childB);
};

#endif /* CROSSOVERTWOPOINT_H_ */
