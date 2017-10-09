/*
 * MutationInversion.cpp
 *
 *  Created on: May 3, 2014
 *      Author: Wojtek
 */

#include "MutationSwappingSegment.h"

MutationSwappingSegment::MutationSwappingSegment() {
	// TODO Auto-generated constructor stub

}

MutationSwappingSegment::~MutationSwappingSegment() {
	// TODO Auto-generated destructor stub
}

void MutationSwappingSegment::performMutation(Chromosom & chromosom) {
	int inversionPointA, inversionPointB;
	const vector<int> & genotype = chromosom.getGenotype();
	vector<int> inversedGenotype;

	inversionPointA = inversionPointB = rand() % genotype.size();
	while (inversionPointA  == inversionPointB)
		inversionPointB = rand() % genotype.size();

	if (inversionPointA > inversionPointB) {
		int temp = inversionPointA;
		inversionPointA = inversionPointB;
		inversionPointB = temp;
	}

	for (vector<int>::const_iterator it = genotype.begin() + inversionPointB; it != genotype.end(); it++)
		inversedGenotype.push_back(*it);

	for (vector<int>::const_iterator it = genotype.begin() + inversionPointA; it != genotype.begin() + inversionPointB; it++)
		inversedGenotype.push_back(*it);

	for (vector<int>::const_iterator it = genotype.begin(); it != genotype.begin() + inversionPointA; it++)
			inversedGenotype.push_back(*it);

	chromosom.setGenotype(inversedGenotype);

	//TODO Usunac wypisywanie w wersji finalnej.
	//cout << "inversionPointA: " << inversionPointA << " inversionPointB: " << inversionPointB << endl;
}

