/*
 * MutationSwapping.cpp
 *
 *  Created on: May 3, 2014
 *      Author: Wojtek
 */

#include "MutationSwappingPoint.h"

MutationSwappingPoint::MutationSwappingPoint() {
	// TODO Auto-generated constructor stub

}

MutationSwappingPoint::~MutationSwappingPoint() {
	// TODO Auto-generated destructor stub
}

void MutationSwappingPoint::performMutation(Chromosom & chromosom) {
	int swappingPointA, swappingPointB;
	vector<int> genotype = chromosom.getGenotype();

	swappingPointA = swappingPointB = rand() % genotype.size();
	while (swappingPointA  == swappingPointB)
		swappingPointB = rand() % genotype.size();

	int temp = genotype[swappingPointA];
	genotype[swappingPointA] = genotype[swappingPointB];
	genotype[swappingPointB] = temp;

	chromosom.setGenotype(genotype);

	//TODO Usunac wypisywanie w wersji finalnej.
	//cout << "swappingPointA: " << swappingPointA << " swappingPointB: " << swappingPointB << endl;
}

