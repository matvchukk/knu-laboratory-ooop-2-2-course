#pragma once
#include "ComplexMatrix.h"
/// @brief Represents a Gauss-Jordan Inverse calculator for complex matrices.
class GaussJordanInverse {
private:
    ComplexMatrix A; ///< The input matrix.
    int rank; ///< The rank of the matrix.
    int columns; ///< The number of columns in the matrix.
    ComplexMatrix tempMatrix; ///< Temporary matrix used in the calculation.

public:
    /// @brief Constructs a GaussJordanInverse object with the specified matrix.
    /// @param matrix The complex matrix for which to calculate the Gauss-Jordan inverse.
    GaussJordanInverse(ComplexMatrix matrix);

    /// @brief Calculates the Gauss-Jordan inverse of the matrix.
    /// @return The calculated Gauss-Jordan inverse matrix.
    ComplexMatrix calculateGaussJordanInverse();
};
