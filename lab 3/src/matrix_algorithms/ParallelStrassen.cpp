#include "ParallelStrassen.h"
/// @brief Performs parallel matrix multiplication using the Strassen algorithm.
    /// @param a The first input matrix.
    /// @param b The second input matrix.
    /// @return Pointer to the resulting matrix.
ComplexMatrix* ParallelStrassen::parallelMultiply(ComplexMatrix* a, ComplexMatrix* b) {
    assert(a->getColumns() == b->getRows());
    int n = a->getColumns();
    int m = a->getRows();
    int q = b->getColumns();
    ComplexMatrix* result = new ComplexMatrix(m, q);

    parallelStrassen(a, b, result, n, m, q);

    return result;
}
/// @brief Performs the recursive step of the Strassen algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @param result The resulting matrix.
/// @param n The size of the input matrices (power of 2).
/// @param m The row offset for matrix a.
/// @param q The column offset for matrix b.
void ParallelStrassen::strassenRecursion(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q) {
    if (n <= 8 || m <= 8 || q <= 8) {
        ParallelStrassen::multiplyBlock(a, b, result, 0, 0, 0, n);
        return;
    }

    int newN = n / 2 + n % 2;
    int newM = m / 2 + m % 2;
    int newQ = q / 2 + q % 2;

    ComplexMatrix a11(newM, newN);
    ComplexMatrix a12(newM, newN);
    ComplexMatrix a21(newM, newN);
    ComplexMatrix a22(newM, newN);

    ComplexMatrix b11(newN, newQ);
    ComplexMatrix b12(newN, newQ);
    ComplexMatrix b21(newN, newQ);
    ComplexMatrix b22(newN, newQ);

    for (int i = 0; i < newM; i++) {
        for (int j = 0; j < newN; j++) {
            a11.set(i, j, a->get(i, j));
            a12.set(i, j, ((j + newN) < n) ? a->get(i, j + newN) : ComplexNum(0, 0));
            a21.set(i, j, ((i + newM) < m) ? a->get(i + newM, j) : ComplexNum(0, 0));
            a22.set(i, j, ((i + newM) < m && (j + newN) < n) ? a->get(i + newM, j + newN) : ComplexNum(0, 0));
        }
    }

    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newQ; j++) {
            b11.set(i, j, b->get(i, j));
            b12.set(i, j, ((j + newQ) < q) ? b->get(i, j + newQ) : ComplexNum(0, 0));
            b21.set(i, j, ((i + newN) < n) ? b->get(i + newN, j) : ComplexNum(0, 0));
            b22.set(i, j, ((i + newN) < n && (j + newQ) < q) ? b->get(i + newN, j + newQ) : ComplexNum(0, 0));
        }
    }

    ComplexMatrix d1 = a11 + a22;
    ComplexMatrix d2 = b11 + b22;
    ComplexMatrix d3 = a21 + a22;
    ComplexMatrix d4 = b12 - b22;
    ComplexMatrix d5 = b21 - b11;
    ComplexMatrix d6 = a11 + a12;
    ComplexMatrix d7 = a21 - a11;
    ComplexMatrix d8 = b11 + b12;
    ComplexMatrix d9 = a12 - a22;
    ComplexMatrix d10 = b21 + b22;

    ComplexMatrix m1(newM, newQ);
    ComplexMatrix m2(newM, newQ);
    ComplexMatrix m3(newM, newQ);
    ComplexMatrix m4(newM, newQ);
    ComplexMatrix m5(newM, newQ);
    ComplexMatrix m6(newM, newQ);
    ComplexMatrix m7(newM, newQ);

    std::thread t1(&ParallelStrassen::strassenRecursion, &d1, &d2, &m1, newN, newM, newQ);
    std::thread t2(&ParallelStrassen::strassenRecursion, &d3, &b11, &m2, newN, newM, newQ);
    std::thread t3(&ParallelStrassen::strassenRecursion, &a11, &d4, &m3, newN, newM, newQ);
    std::thread t4(&ParallelStrassen::strassenRecursion, &a22, &d5, &m4, newN, newM, newQ);
    std::thread t5(&ParallelStrassen::strassenRecursion, &d6, &b22, &m5, newN, newM, newQ);
    std::thread t6(&ParallelStrassen::strassenRecursion, &d7, &d8, &m6, newN, newM, newQ);
    std::thread t7(&ParallelStrassen::strassenRecursion, &d9, &d10, &m7, newN, newM, newQ);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    ComplexMatrix r1 = m1 + m4 - m5 + m7;
    ComplexMatrix r2 = m3 + m5;
    ComplexMatrix r3 = m2 + m4;
    ComplexMatrix r4 = m1 - m2 + m3 + m6;

    for (int i = 0; i < newM; i++) {
        for (int j = 0; j < newQ; j++) {
            result->set(i, j, r1.get(i, j));
            if ((j + newQ) < q) {
                result->set(i, j + newQ, r2.get(i, j));
            }
            if ((i + newM) < m) {
                result->set(i + newM, j, r3.get(i, j));
            }
            if ((i + newM) < m && (j + newQ) < q) {
                result->set(i + newM, j + newQ, r4.get(i, j));
            }
        }
    }
}
/// @brief Performs the parallel implementation of the Strassen algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @param result The resulting matrix.
/// @param n The size of the input matrices (power of 2).
/// @param m The row offset for matrix a.
/// @param q The column offset for matrix b.
void ParallelStrassen::parallelStrassen(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q) {
    int blockSize = 256;
    int numThreads = std::thread::hardware_concurrency();
    int blocks = n / blockSize;

    if (blocks * blockSize < n) {
        blocks++;
    }

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < blocks; j++) {
            ComplexMatrix* blockResult = new ComplexMatrix(blockSize, blockSize);
            int rowA = i * blockSize;
            int colB = j * blockSize;

            for (int k = 0; k < blocks; k++) {
                int colA = k * blockSize;
                multiplyBlock(a, b, blockResult, rowA, colA, colB, blockSize);
                addBlock(result, blockResult, result, rowA, colB, 0, 0, blockSize);
            }

            delete blockResult;
        }
    }


    for (std::thread& thread : threads) {
        thread.join();
    }
}

/// @brief Multiplies a block of matrices using the standard matrix multiplication algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @param result The resulting matrix.
/// @param rowA The starting row index for matrix a.
/// @param colA The starting column index for matrix a.
/// @param colB The starting column index for matrix b.
/// @param blockSize The size of the block.
void ParallelStrassen::multiplyBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int colB, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            ComplexNum sum(0, 0);
            for (int k = 0; k < blockSize; k++) {
                sum = sum + a->get(rowA + i, colA + k) * b->get(colA + k, colB + j);
            }
            result->set(i, j, sum);
        }
    }
}
/// @brief Adds a block of matrices element-wise.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @param result The resulting matrix.
/// @param rowA The starting row index for matrix a.
/// @param colA The starting column index for matrix a.
/// @param rowB The starting row index for matrix b.
/// @param colB The starting column index for matrix b.
/// @param blockSize The size of the block.
void ParallelStrassen::addBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            result->set(rowA + i, colA + j, a->get(rowA + i, colA + j) + b->get(rowB + i, colB + j));
        }
    }
}

/// @brief Subtracts a block of matrices element-wise.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @param result The resulting matrix.
/// @param rowA The starting row index for matrix a.
/// @param colA The starting column index for matrix a.
/// @param rowB The starting row index for matrix b.
/// @param colB The starting column index for matrix b.
/// @param blockSize The size of the block.
void ParallelStrassen::subtractBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            result->set(rowA + i, colA + j, a->get(rowA + i, colA + j) - b->get(rowB + i, colB + j));
        }
    }
}
