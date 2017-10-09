//
//  OccupationTrait.h
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__OccupationTrait__
#define __Network_Dynamics__OccupationTrait__

#include "Trait.h"

class OccupationTrait: public Trait {
public:
    /**
     
     */
    enum Occupation {
      Student, Employed, Unemployed, COUNT
    };
    
    /**
     OccupationTrait class default constructor.
     */
    OccupationTrait();
    
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
    Occupation value;
};
#endif /* defined(__Network_Dynamics__OccupationTrait__) */
