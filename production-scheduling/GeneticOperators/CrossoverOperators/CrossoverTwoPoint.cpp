/*
 * CrossoverTwoPoint.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Wojtek
 */

#include "CrossoverTwoPoint.h"

CrossoverTwoPoint::CrossoverTwoPoint() {
	// TODO Auto-generated constructor stub

}

CrossoverTwoPoint::~CrossoverTwoPoint() {
	// TODO Auto-generated destructor stub
}

void CrossoverTwoPoint::crossChromosoms(const Chromosom & parentA, const Chromosom & parentB, Chromosom & childA, Chromosom & childB) {
	int crossoverPointA, crossoverPointB;
	const vector<int> & parentAGenotype = parentA.getGenotype();
	const vector<int> & parentBGenotype = parentB.getGenotype();
	vector<int> childAGenotype = parentA.getGenotype();
	vector<int> childBGenotype = parentB.getGenotype();

	crossoverPointA = crossoverPointB = (rand() % (parentAGenotype.size() - 2)) + 1;
	while (crossoverPointA  == crossoverPointB)
		crossoverPointB = (rand() % (parentAGenotype.size() - 2)) + 1;

	if (crossoverPointA > crossoverPointB) {
		int temp = crossoverPointA;
		crossoverPointA = crossoverPointB;
		crossoverPointB = temp;
	}

	//TODO Usunac w finalnej wersji.
	//cout << "Crossover Point1: " << crossoverPointA << " Crossover Point2: " << crossoverPointB << endl;

	for(int i = 0; i < crossoverPointA; i++) {
		childAGenotype[i] = parentBGenotype[i];
		childBGenotype[i] = parentAGenotype[i];
	}

	for(int i = 0; i < crossoverPointB; i++) {
		childAGenotype[i] = parentBGenotype[i];
		childBGenotype[i] = parentAGenotype[i];
	}

	childA.setGenotype(childAGenotype);
	childB.setGenotype(childBGenotype);
}
