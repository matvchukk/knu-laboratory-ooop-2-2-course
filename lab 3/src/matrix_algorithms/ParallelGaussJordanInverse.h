#pragma once
#include "ComplexMatrix.h"
#include <vector>
#include <mutex>
#include <algorithm>
#include <thread>

class ParallelGaussJordanInverse {
private:
    ComplexMatrix A;
    int rank;
    int columns;
    ComplexMatrix tempMatrix;
    std::mutex mtx;

public:
    ParallelGaussJordanInverse(ComplexMatrix matrix);

    ComplexMatrix calculateParallelGaussJordanInverse();
};

