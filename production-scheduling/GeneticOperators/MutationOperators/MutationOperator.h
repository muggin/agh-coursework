/*
 * MutationOperator.h
 *
 *  Created on: May 1, 2014
 *      Author: Wojtek
 */

#ifndef MUTATIONOPERATOR_H_
#define MUTATIONOPERATOR_H_
#include "../../Algorithm/Chromosom.h"

class MutationOperator {
public:
	MutationOperator();
	virtual ~MutationOperator();

	/**
	 * Funkcja dokonuje mutacji chromosomu.
	 * \param chromosom osobnik ktory podlega mutacji.
	 */
	virtual void performMutation(Chromosom & chromosom) = 0;

    void identifyObject();
};

#endif /* MUTATIONOPERATOR_H_ */
