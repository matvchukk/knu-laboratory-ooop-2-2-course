#pragma once
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"
/// @brief Represents an LU Inverse calculator for complex matrices.
class LUInverse {
public:
    /// @brief Performs LU decomposition of the input matrix.
    /// @param a The input matrix to be decomposed.
    /// @param l The lower triangular matrix resulting from the decomposition.
    /// @param u The upper triangular matrix resulting from the decomposition.
    /// @return True if the LU decomposition was successful, false otherwise.
    static bool LUDecomposition(ComplexMatrix a, ComplexMatrix& l, ComplexMatrix& u);

    /// @brief Creates an empty array of ComplexNum objects.
    /// @param n The size of the array.
    /// @return A pointer to the created array.
    static ComplexNum* createEmpty(int n);

    /// @brief Performs forward substitution to solve a lower triangular system of equations.
    /// @param l The lower triangular matrix.
    /// @param vector The right-hand side vector.
    /// @param n The size of the system.
    /// @return The solution vector.
    static ComplexNum* forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int n);

    /// @brief Performs back substitution to solve an upper triangular system of equations.
    /// @param u The upper triangular matrix.
    /// @param vector The right-hand side vector.
    /// @param n The size of the system.
    /// @return The solution vector.
    static ComplexNum* backSubstitution(ComplexMatrix u, ComplexNum* vector, int n);

    /// @brief Calculates the LU inverse of the input matrix.
    /// @param a The input matrix for which to calculate the LU inverse.
    /// @return The calculated LU inverse matrix.
    static ComplexMatrix calculateLUInverse(ComplexMatrix a);
};
