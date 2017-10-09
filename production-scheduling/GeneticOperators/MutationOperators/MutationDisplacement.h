#ifndef MUTATIONDISPLACEMENT_H
#define MUTATIONDISPLACEMENT_H

#include <algorithm>
#include "MutationOperator.h"

class MutationDisplacement : public MutationOperator
{
public:
    MutationDisplacement();
    virtual ~MutationDisplacement();

    /**
     * Funkcja dokonuje mutacji chromosomu poprzez odwrócenie kolejności genotypu.
     * performMutation wykorzystuje funkcję biblioteczną reverse() do odwrócenia kolejnosci genotypu osobnika.
     * \param chromosom osobnik który podlega mutacji.
     */
    void performMutation(Chromosom & chromosom);
};

#endif // MUTATIONDISPLACEMENT_H
