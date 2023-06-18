#include "MatrixInverseFactory.h"

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
