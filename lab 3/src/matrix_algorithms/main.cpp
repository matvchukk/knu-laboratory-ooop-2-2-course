// matrix_algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ComplexNum.h"
#include "ComplexMatrix.h"
#include "LUInverse.h"
#include "GaussJordanInverse.h"

int main() {
    // Generate random matrix
    int matrixSize = 4;
    ComplexMatrix A(matrixSize, matrixSize);
    A.auto_gen(5, 50, 5, 50);
    std::cout << "Random Matrix A:" << std::endl;
    A.print();

    ComplexMatrix E(matrixSize, matrixSize);

    for (int i = 0; i < matrixSize; i++)
        E.set(i, i, ComplexNum(1));

    // Perform LU decomposition
    ComplexMatrix L(matrixSize, matrixSize);
    ComplexMatrix U(matrixSize, matrixSize);
    if (LUInverse::LUDecomposition(A, L, U)) {
        std::cout << "LU Decomposition:" << std::endl;
        std::cout << "L:" << std::endl;
        L.print();
        std::cout << "U:" << std::endl;
        U.print();
    }
    else {
        std::cout << "LU decomposition failed." << std::endl;
    }

    // Perform inverse matrix calculation using LU decomposition
    ComplexMatrix inverseA = LUInverse::calculateLUInverse(A);
    if (inverseA.getRows() != 0) {
        std::cout << "Inverse Matrix:" << std::endl;
        inverseA.print();
    }
    else {
        std::cout << "Inverse matrix calculation failed." << std::endl;
    }

    // Perform Gauss-Jordan inversion
    int matrixRank = 10;
    ComplexMatrix randomMatrix(matrixRank, matrixRank);
    randomMatrix.auto_gen(1, 10, 1, 10);
    std::cout << "Random Matrix for Gauss-Jordan Inversion:" << std::endl;
    randomMatrix.print();
    GaussJordanInverse gaussJordanInverse(randomMatrix);
    ComplexMatrix inverseMatrix = gaussJordanInverse.calculate();
    std::cout << "Inverse Matrix using Gauss-Jordan Inversion:" << std::endl;
    inverseMatrix.print();

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file