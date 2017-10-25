#include "MutationDisplacement.h"

MutationDisplacement::MutationDisplacement() {

}

MutationDisplacement::~MutationDisplacement() {

}

void MutationDisplacement::performMutation(Chromosom & chromosom) {
     vector<int> displacedGenotype = chromosom.getGenotype();
     vector<int> tempGenes;
     int segmentStart = rand() % (displacedGenotype.size() - 2);
     int segmentSize = rand() % (displacedGenotype.size() - segmentStart - 2) + 1;
     int segmentEnd = segmentStart + segmentSize;
     int newSegmentStart = segmentStart;

     for(vector<int>::iterator it = displacedGenotype.begin() + segmentStart; it != displacedGenotype.begin() + segmentEnd; it++) {
         tempGenes.push_back(*it);
     }

     displacedGenotype.erase(displacedGenotype.begin() + segmentStart, displacedGenotype.begin() + segmentEnd);

     while (newSegmentStart == segmentStart)
         newSegmentStart = rand() % (displacedGenotype.size());

     displacedGenotype.insert(displacedGenotype.begin() + newSegmentStart, tempGenes.begin(), tempGenes.end());
     chromosom.setGenotype(displacedGenotype);
}
