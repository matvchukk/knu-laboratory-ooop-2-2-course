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
/// @brief Represents a factory for calculating matrix inverses using different algorithms.
class MatrixInverseFactory {
public:
    /// @brief Calculates the inverse of the given matrix using the specified algorithm.
    /// @param matrix The input matrix for which to calculate the inverse.
    /// @param algorithm The algorithm to be used for the inverse calculation.
    /// @return The calculated inverse matrix.
    static ComplexMatrix calculateInverse(const ComplexMatrix& matrix, InverseAlgorithm algorithm);
};
