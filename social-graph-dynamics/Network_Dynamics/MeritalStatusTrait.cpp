//
//  MeritalStatusTrait.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "MeritalStatusTrait.h"

using namespace std;

MeritalStatusTrait::MeritalStatusTrait() {
    //TODO Replace with final version based on distribution.
    int randomIndex = rand() % MeritalStatus::COUNT;
    this->value = MeritalStatus(randomIndex);
}

int MeritalStatusTrait::getValue() const {
    return this->value;
}

string MeritalStatusTrait::toString() const {
    string toString;
    switch (this->value) {
        case 0: toString = "Single";
            break;
        case 1: toString = "Relationship";
            break;
        case 2: toString = "Married";
            break;
        case 3: toString = "Divorced";
            break;
        case 4: toString = "Widowed";
            break;
    }
    return toString;
}