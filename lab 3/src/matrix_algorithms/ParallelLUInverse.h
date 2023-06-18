#pragma once
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"
#include <thread>
#include <vector>
/// @brief Represents a class for calculating the inverse of a matrix using LU decomposition in parallel.
class ParallelLUInverse {
public:
    /// @brief Performs LU decomposition of the input matrix in parallel.
    /// @param a The input matrix to decompose.
    /// @param l The lower triangular matrix (output).
    /// @param u The upper triangular matrix (output).
    /// @return True if the decomposition is successful, false otherwise.
    static bool parallelLUDecomposition(ComplexMatrix a, ComplexMatrix& l, ComplexMatrix& u);

    /// @brief Creates an empty complex number array of size n.
    /// @param n The size of the array.
    /// @return Pointer to the created array.
    static ComplexNum* createEmpty(int n);

    /// @brief Performs forward substitution for solving a system of equations with a lower triangular matrix.
    /// @param l The lower triangular matrix.
    /// @param vector The input vector.
    /// @param n The size of the matrix and vector.
    /// @return Pointer to the solution vector.
    static ComplexNum* forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int n);

    /// @brief Performs back substitution for solving a system of equations with an upper triangular matrix.
    /// @param u The upper triangular matrix.
    /// @param vector The input vector.
    /// @param n The size of the matrix and vector.
    /// @return Pointer to the solution vector.
    static ComplexNum* backSubstitution(ComplexMatrix u, ComplexNum* vector, int n);

    /// @brief Calculates the inverse of the input matrix using LU decomposition in parallel.
    /// @param a The input matrix.
    /// @return The calculated inverse matrix.
    static ComplexMatrix calculateParallelLUInverse(ComplexMatrix a);
};
