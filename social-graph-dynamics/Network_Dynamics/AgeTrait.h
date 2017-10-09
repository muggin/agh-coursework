//
//  AgeTrait.h
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__AgeTrait__
#define __Network_Dynamics__AgeTrait__

#include "Trait.h"

class AgeTrait: public Trait {
private:
    /**
     Static array holding statistic data about the distribution of age groups.
     */
    constexpr static const double distribution[] = { 0.217, 0.316, 0.262, 0.167, 0.038 };
    
public:
    /**
     Enum
     */
    enum Age {
        Adolescent, YoungAdult, Adult, Old, VeryOld, COUNT
    };
    
    /**
     AgeTrait class default constructor.
     */
    AgeTrait();
    
    /**
     @see Description of method available in base class header. (Trait.h)
     */
    int getValue() const;
    
    /**
     @see Description of method available in base class header. (Trait.h)
     */
    std::string toString() const;
    
    double compareWithTrait(const Trait& trait) const;
private:
    /**
     
     */
    Age value;
};

#endif /* defined(__Network_Dynamics__AgeTrait__) */
