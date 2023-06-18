#pragma once
#include <iostream>
#include "ComplexMatrix.h"
#include <thread>
#include <vector>
/// @brief Represents a class for performing matrix multiplication using the parallel implementation of the Strassen algorithm.
class ParallelStrassen {
public:
    /// @brief Performs parallel matrix multiplication using the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @return Pointer to the resulting matrix.
    static ComplexMatrix* parallelMultiply(ComplexMatrix* a, ComplexMatrix* b);
private:
    /// @brief Performs the recursive step of the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @param result The resulting matrix.
    /// @param n The size of the input matrices (power of 2).
    /// @param m The row offset for matrix a.
    /// @param q The column offset for matrix b.
    static void strassenRecursion(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q);

    /// @brief Performs the parallel implementation of the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @param result The resulting matrix.
    /// @param n The size of the input matrices (power of 2).
    /// @param m The row offset for matrix a.
    /// @param q The column offset for matrix b.
    static void parallelStrassen(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q);

    /// @brief Multiplies a block of matrices using the standard matrix multiplication algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @param result The resulting matrix.
    /// @param rowA The starting row index for matrix a.
    /// @param colA The starting column index for matrix a.
    /// @param colB The starting column index for matrix b.
    /// @param blockSize The size of the block.
    static void multiplyBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int colB, int blockSize);

    /// @brief Adds a block of matrices element-wise.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @param result The resulting matrix.
    /// @param rowA The starting row index for matrix a.
    /// @param colA The starting column index for matrix a.
    /// @param rowB The starting row index for matrix b.
    /// @param colB The starting column index for matrix b.
    /// @param blockSize The size of the block.
    static void addBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize);

    /// @brief Subtracts a block of matrices element-wise.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @param result The resulting matrix.
    /// @param rowA The starting row index for matrix a.
    /// @param colA The starting column index for matrix a.
    /// @param rowB The starting row index for matrix b.
    /// @param colB The starting column index for matrix b.
    /// @param blockSize The size of the block.
    static void subtractBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize);
};

