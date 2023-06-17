#pragma once
#include "ComplexMatrix.h"

class GaussJordanInverse {
private:
    ComplexMatrix A;
    int rank;
    int columns;
    ComplexMatrix tempMatrix;

public:
    GaussJordanInverse(ComplexMatrix matrix);

    ComplexMatrix calculate();
};
