//
//  OccupationTrait.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "OccupationTrait.h"

using namespace std;

OccupationTrait::OccupationTrait() {
    //TODO Replace with final version based on distribution.
    int randomIndex = rand() % Occupation::COUNT;
    this->value = Occupation(randomIndex);
}

int OccupationTrait::getValue() const {
    return this->value;
}

string OccupationTrait::toString() const {
    string toString;
    switch (this->value) {
        case 0: toString = "Student";
            break;
        case 1: toString = "Employed";
            break;
        case 2: toString = "Unemployed";
            break;
    }
    return toString;
}