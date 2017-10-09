//
//  AgeTrait.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "AgeTrait.h"

using namespace std;

AgeTrait::AgeTrait() {
    //TODO Replace with final version based on distribution.
    int randomIndex = rand() % Age::COUNT;
    this->value = Age(randomIndex);
}

int AgeTrait::getValue() const {
    return this->value;
}

string AgeTrait::toString() const {
    string toString;
    switch (this->value) {
        case 0: toString = "Adolescent";
            break;
        case 1: toString = "Young Adult";
            break;
        case 2: toString = "Adult";
            break;
        case 3: toString = "Old";
            break;
        case 4: toString = "VeryOld";
            break;
    }
    return toString;
}

double AgeTrait::compareWithTrait(const Trait& trait) const {
    return  1.0 - (double) abs(this->getValue() - trait.getValue()) / Age::COUNT;
}
