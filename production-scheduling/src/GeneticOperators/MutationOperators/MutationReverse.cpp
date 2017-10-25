/*
 * MutationReverse.cpp
 *
 *  Created on: May 10, 2014
 *      Author: Wojtek
 */

#include "MutationReverse.h"

MutationReverse::MutationReverse() {
	// TODO Auto-generated constructor stub
}

MutationReverse::~MutationReverse() {
	// TODO Auto-generated destructor stub
}

void MutationReverse::performMutation(Chromosom & chromosom) {
	vector<int> reversedGenotype = chromosom.getGenotype();
	reverse(reversedGenotype.begin(), reversedGenotype.end());
	chromosom.setGenotype(reversedGenotype);
}
