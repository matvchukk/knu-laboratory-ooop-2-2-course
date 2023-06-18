#pragma once
#include <iostream>
#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "Strassen.h"
#include <thread>
#include <vector>

class ParallelLUInverse {
public:
    static bool parallelLUDecomposition(ComplexMatrix a, ComplexMatrix& l, ComplexMatrix& u);

    static ComplexNum* createEmpty(int n);

    static ComplexNum* forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int n);

    static ComplexNum* backSubstitution(ComplexMatrix u, ComplexNum* vector, int n);

    static ComplexMatrix calculateParallelLUInverse(ComplexMatrix a);
};
//#pragma once
//#include "ComplexMatrix.h"
//#include <vector>
//#include <mutex>
//#include <algorithm>
//#include <thread>
//#include "LUInverse.h"
//
//class ParallelLUInverse {
//private:
//    ComplexMatrix A;
//    int rank;
//    int columns;
//    ComplexMatrix lMatrix;
//    ComplexMatrix uMatrix;
//    std::mutex mtx;
//
//public:
//    ParallelLUInverse(ComplexMatrix matrix);
//
//    static ComplexMatrix calculateParallelLUInverse(ComplexMatrix a);
//};
