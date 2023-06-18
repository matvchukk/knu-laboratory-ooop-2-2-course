#pragma once
#include <iostream>
#include "ComplexMatrix.h"
#include <thread>
#include <vector>

class ParallelStrassen {
public:
    static ComplexMatrix* parallelMultiply(ComplexMatrix* a, ComplexMatrix* b);

private:
    static void strassenRecursion(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q);
    static void parallelStrassen(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int n, int m, int q);
    static void multiplyBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int colB, int blockSize);
    static void addBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize);
    static void subtractBlock(ComplexMatrix* a, ComplexMatrix* b, ComplexMatrix* result, int rowA, int colA, int rowB, int colB, int blockSize);
};

