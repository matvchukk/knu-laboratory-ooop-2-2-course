#pragma once
#include <chrono> 
#include "MatrixInverseFactory.h"
/// @brief Represents a matrix inverse factory that measures the execution time of the underlying factory.
class TimeMatrixInverseFactory : public MatrixInverseFactory {
private:
    MatrixInverseFactory& factory;///< The underlying matrix inverse factory.
    InverseAlgorithm algorithm;///< The algorithm used for calculating the inverse.
public:
    /// @brief Constructs a `TimeMatrixInverseFactory` object with the specified factory and algorithm.
    /// @param factory The underlying matrix inverse factory.
    /// @param algorithm The algorithm to be used for calculating the inverse.
    TimeMatrixInverseFactory(MatrixInverseFactory& factory, InverseAlgorithm algorithm)
        : factory(factory), algorithm(algorithm) {}

    /// @brief Calculates the inverse of the given matrix and measures the execution time.
    /// @param matrix The input matrix.
    /// @return The inverse matrix.
    ComplexMatrix calculateInverse(const ComplexMatrix& matrix) {
        auto start = std::chrono::high_resolution_clock::now();

        ComplexMatrix inverse = factory.calculateInverse(matrix, algorithm);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        //std::cout << "Elapsed time: " << duration.count() << " milliseconds" << std::endl;
        return inverse;
    }
};
