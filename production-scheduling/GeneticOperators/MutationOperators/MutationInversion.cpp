#include "MutationInversion.h"

MutationInversion::MutationInversion()
{
}

MutationInversion::~MutationInversion()
{
}

void MutationInversion::performMutation(Chromosom & chromosom) {
    int inversionPointA, inversionPointB;
    vector<int> invertedGenotype = chromosom.getGenotype();

    inversionPointA = inversionPointB = (rand() % (invertedGenotype.size() - 2)) + 1;
    while (inversionPointA  == inversionPointB)
        inversionPointB = rand() % (invertedGenotype.size() - 2);

    if (inversionPointA > inversionPointB) {
        int temp = inversionPointA;
        inversionPointA = inversionPointB;
        inversionPointB = temp;
    }

    reverse(invertedGenotype.begin() + inversionPointA, invertedGenotype.begin() + inversionPointB);
    chromosom.setGenotype(invertedGenotype);
}
