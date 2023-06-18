#pragma once
#include "ComplexMatrix.h"
#include "LUInverse.h"
#include "ParallelLUInverse.h"
#include "GaussJordanInverse.h"
#include "ParallelGaussJordanInverse.h"

enum class InverseAlgorithm {
    LU,
    ParallelLU,
    GaussJordan,
    ParallelGaussJordan
};

class MatrixInverseFactory {
public:
    static ComplexMatrix calculateInverse(const ComplexMatrix& matrix, InverseAlgorithm algorithm);
};
