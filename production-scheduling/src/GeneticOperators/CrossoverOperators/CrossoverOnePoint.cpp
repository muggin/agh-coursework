/*
 * CrossoverOnePoint.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#include "CrossoverOnePoint.h"

CrossoverOnePoint::CrossoverOnePoint() {
	// TODO Auto-generated constructor stub

}

CrossoverOnePoint::~CrossoverOnePoint() {
	// TODO Auto-generated destructor stub
}

void CrossoverOnePoint::crossChromosoms(const Chromosom & parentA, const Chromosom & parentB, Chromosom & childA, Chromosom & childB) {
	int crossoverPoint;
	const vector<int> & parentAGenotype = parentA.getGenotype();
	const vector<int> & parentBGenotype = parentB.getGenotype();
	vector<int> childAGenotype = parentA.getGenotype();
	vector<int> childBGenotype = parentB.getGenotype();

    crossoverPoint = (rand() % (parentAGenotype.size() - 2)) + 1;

	for(int i = 0; i < crossoverPoint; i++) {
		childAGenotype[i] = parentBGenotype[i];
		childBGenotype[i] = parentAGenotype[i];
	}

	childA.setGenotype(childAGenotype);
	childB.setGenotype(childBGenotype);
}

