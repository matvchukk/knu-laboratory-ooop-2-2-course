#pragma once
#include <chrono> 
#include "MatrixInverseFactory.h"

class TimeMatrixInverseFactory : public MatrixInverseFactory {
public:
    TimeMatrixInverseFactory(MatrixInverseFactory& factory, InverseAlgorithm algorithm)
        : factory(factory), algorithm(algorithm) {}

    ComplexMatrix calculateInverse(const ComplexMatrix& matrix) {
        auto start = std::chrono::high_resolution_clock::now();

        ComplexMatrix inverse = factory.calculateInverse(matrix, algorithm);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        //std::cout << "Elapsed time: " << duration.count() << " milliseconds" << std::endl;

        return inverse;
    }

private:
    MatrixInverseFactory& factory;
    InverseAlgorithm algorithm;
};
