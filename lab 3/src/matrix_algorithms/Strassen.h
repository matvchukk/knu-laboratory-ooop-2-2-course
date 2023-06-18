#pragma once
#include <iostream>
#include "ComplexMatrix.h"
/// @brief Represents a class for performing matrix multiplication using the Strassen algorithm.
class Strassen {
public:
    /// @brief Performs matrix multiplication using the regular algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @return Pointer to the resulting matrix.
    static ComplexMatrix* regularMult(ComplexMatrix* a, ComplexMatrix* b);

    /// @brief Performs the recursive step of the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @return Pointer to the resulting matrix.
    static ComplexMatrix* strassenRecursion(ComplexMatrix* a, ComplexMatrix* b);

    /// @brief Performs matrix multiplication using the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @return Pointer to the resulting matrix.
    static ComplexMatrix* strassenMultiply(ComplexMatrix* a, ComplexMatrix* b);
};
