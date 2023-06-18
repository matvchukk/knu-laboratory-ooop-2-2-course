#pragma once
#include "ComplexMatrix.h"
#include <vector>
#include <mutex>
#include <algorithm>
#include <thread>
/// @brief Represents a class for calculating the inverse of a matrix using the Gauss-Jordan elimination algorithm in parallel.
class ParallelGaussJordanInverse {
private:
    ComplexMatrix A; ///< The input matrix.
    int rank; ///< The rank of the input matrix.
    int columns; ///< The number of columns in the input matrix.
    ComplexMatrix tempMatrix; ///< A temporary matrix for intermediate calculations.
    std::mutex mtx; ///< Mutex for thread safety.

public:
    /// @brief Constructs a ParallelGaussJordanInverse object with the specified matrix.
    /// @param matrix The input matrix for which to calculate the inverse.
    ParallelGaussJordanInverse(ComplexMatrix matrix);

    /// @brief Calculates the inverse of the input matrix using the Gauss-Jordan elimination algorithm in parallel.
    /// @return The calculated inverse matrix.
    ComplexMatrix calculateParallelGaussJordanInverse();
};

