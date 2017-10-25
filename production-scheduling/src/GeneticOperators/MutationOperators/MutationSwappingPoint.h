/*
 * MutationSwapping.h
 *
 *  Created on: May 3, 2014
 *      Author: Wojtek
 */

#ifndef MUTATIONSWAPPINGPOINT_H_
#define MUTATIONSWAPPINGPOINT_H_

#include "MutationOperator.h"

class MutationSwappingPoint: public MutationOperator {

public:

	/**
	 * Konstruktor klasy MutationSwappingPoint.
	 */
	MutationSwappingPoint();

	/**
	 * Destruktor klasy MutationSwappingPoint.
	 */
	virtual ~MutationSwappingPoint();

	/**
	 * Funkcja dokonuje mutacji chromosomu poprzez zamianę pojedyńczych genow.
	 * Losowane sa dwa różne geny w genotypu osobnika, które następni są zamieniane miejscami.
	 * \param chromosom osobnik ktory podlega mutacji.
	 */
	void performMutation(Chromosom & chromosom);
};

#endif /* MUTATIONSWAPPINGPOINT_H_ */
