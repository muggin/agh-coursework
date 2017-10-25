/*
 * MutationInversion.h
 *
 *  Created on: May 3, 2014
 *      Author: Wojtek
 */

#ifndef MUTATIONSWAPPINGSEGMENT_H_
#define MUTATIONSWAPPINGSEGMENT_H_

#include "MutationOperator.h"

class MutationSwappingSegment: public MutationOperator {
public:

	/**
	 * Konstruktor klasy MutationSwappingSegment.
	 */
	MutationSwappingSegment();

	/**
	 * Destruktor klasy MutationSwappingSegment.
	 */
	virtual ~MutationSwappingSegment();

	/**
	 * Funkcja dokonuje mutacji chromosomu poprzez inwersje dwóch segmentów chromosomu.
	 * Losowane są dwa różne segmenty genotypu osobnika które następnie są zamieniane miejscami.
	 * \param chromosom osobnik ktory podlega mutacji.
	 */
	void performMutation(Chromosom & chromosom);
};

#endif /* MUTATIONSWAPPINGSEGMENT_H_ */
