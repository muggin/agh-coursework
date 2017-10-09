#ifndef MUTATIONINVERSION_H
#define MUTATIONINVERSION_H

#include <algorithm>
#include "MutationOperator.h"

class MutationInversion : public MutationOperator
{
public:
    MutationInversion();
    virtual ~MutationInversion();

    /**
     * Funkcja dokonuje mutacji chromosomu poprzez odwrócenie kolejności genotypu.
     * performMutation wykorzystuje funkcję biblioteczną reverse() do odwrócenia kolejnosci genotypu osobnika.
     * \param chromosom osobnik który podlega mutacji.
     */
    void performMutation(Chromosom & chromosom);
};

#endif // MUTATIONINVERSION_H
