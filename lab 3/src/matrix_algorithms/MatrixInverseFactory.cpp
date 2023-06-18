#include "MatrixInverseFactory.h"
/// @brief Calculates the inverse of the given matrix using the specified algorithm.
/// @param matrix The input matrix for which to calculate the inverse.
/// @param algorithm The algorithm to be used for the inverse calculation.
/// @return The calculated inverse matrix.
ComplexMatrix MatrixInverseFactory::calculateInverse(const ComplexMatrix& matrix, InverseAlgorithm algorithm) {
    switch (algorithm) {
    case InverseAlgorithm::LU:
        return LUInverse::calculateLUInverse(matrix);
    case InverseAlgorithm::ParallelLU:
        return ParallelLUInverse::calculateParallelLUInverse(matrix);
    case InverseAlgorithm::GaussJordan: {
        GaussJordanInverse gaussJordan(matrix);
        return gaussJordan.calculateGaussJordanInverse();
    }
    case InverseAlgorithm::ParallelGaussJordan: {
        ParallelGaussJordanInverse parallelGaussJordan(matrix);
        return parallelGaussJordan.calculateParallelGaussJordanInverse();
    }
    default:
        throw std::runtime_error("Invalid inverse algorithm chosen");
    }
}
