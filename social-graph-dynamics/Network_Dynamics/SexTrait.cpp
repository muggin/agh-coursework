//
//  SexTrait.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "SexTrait.h"

using namespace std;

SexTrait::SexTrait() {
    //TODO Replace with final version based on distribution.
    int randomIndex = rand() % Sex::COUNT;
    this->value = Sex(randomIndex);
}

int SexTrait::getValue() const {
    return this->value;
}

string SexTrait::toString() const {
    string toString;
    switch (this->value) {
        case 0: toString = "Male";
            break;
        case 1: toString = "Female";
            break;
    }
    return toString;
}