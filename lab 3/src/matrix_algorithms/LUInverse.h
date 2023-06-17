#pragma once
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"

class LUInverse {
public:
    static bool LUDecomposition(ComplexMatrix a, ComplexMatrix& l, ComplexMatrix& u);

    static ComplexNum* createEmpty(int n);

    static ComplexNum* forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int n);

    static ComplexNum* backSubstitution(ComplexMatrix u, ComplexNum* vector, int n);

    static ComplexMatrix calculateLUInverse(ComplexMatrix a);
};
