/*
 * MutationReverse.h
 *
 *  Created on: May 10, 2014
 *      Author: Wojtek
 */

#ifndef MUTATIONREVERSE_H_
#define MUTATIONREVERSE_H_

#include <algorithm>
#include "MutationOperator.h"
using namespace std;

class MutationReverse: public MutationOperator {
public:
	/**
	 * Konstruktor klasy MutationReverse.
	 */
	MutationReverse();

	/**
	 * Destruktor klasy MutationReverse.
	 */
	virtual ~MutationReverse();

	/**
	 * Funkcja dokonuje mutacji chromosomu poprzez odwrócenie kolejności genotypu.
	 * performMutation wykorzystuje funkcję biblioteczną reverse() do odwrócenia kolejnosci genotypu osobnika.
	 * \param chromosom osobnik który podlega mutacji.
	 */
	void performMutation(Chromosom & chromosom);
};

#endif /* MUTATIONREVERSE_H_ */
