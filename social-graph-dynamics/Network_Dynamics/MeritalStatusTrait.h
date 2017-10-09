//
//  MeritalStatusTrait.h
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__MeritalStatusTrait__
#define __Network_Dynamics__MeritalStatusTrait__

#include "Trait.h"

class MeritalStatusTrait: public Trait {
public:
    /**
     
     */
    enum MeritalStatus {
        Single, Relationship, Married, Divorced, Widowed, COUNT
    };
    
    /**
     MeritalStatusTrait class default constructor.
     */
    MeritalStatusTrait();
    
    /**
     @see Description of method available in base class header. (Trait.h)
     */
    int getValue() const;
    
    /**
     @see Description of method available in base class header. (Trait.h)
     */
    std::string toString() const;

private:
    /**
     */
    MeritalStatus value;
    
};

#endif /* defined(__Network_Dynamics__MeritalStatusTrait__) */
