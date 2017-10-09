//
//  SexTrait.h
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__SexTrait__
#define __Network_Dynamics__SexTrait__

#include <vector>
#include "Trait.h"

class SexTrait: public Trait {
private:
    /**
     Static array holding statistic data about the distribution of gender.
     */
    constexpr static const double statistics[] = { 0.515, 0.485 };
    
public:
    /**
     
     */
    enum Sex {
        Male, Female, COUNT
    };
    
    /**
     SexTrait class default constructor.
     */
    SexTrait();
    
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
    Sex value;
};

#endif /* defined(__Network_Dynamics__SexTrait__) */
