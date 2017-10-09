//
//  Trait.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "Trait.h"

using namespace std;



double Trait::operator&&(const Trait& traitA) {
    return this->compareWithTrait(traitA);
}

double Trait::compareWithTrait(const Trait& trait) const {
    double returnValue;
    this->getValue() == trait.getValue() ? returnValue = 1.0 : returnValue = 0.0;
    return returnValue;
}

ostream& operator<< (ostream& os, const Trait& trait) {
    return os << trait.toString();
}

