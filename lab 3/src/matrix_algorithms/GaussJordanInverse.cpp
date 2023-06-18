#include "GaussJordanInverse.h"
#include <algorithm>
/// @brief Constructs a GaussJordanInverse object with the specified matrix.
/// @param matrix The complex matrix for which to calculate the Gauss-Jordan inverse.
GaussJordanInverse::GaussJordanInverse(ComplexMatrix matrix) {
    A = matrix;
    rank = A.getRows();
    columns = A.getColumns();

    assert(rank == columns);
    assert(rank == A.getRank());

    tempMatrix = ComplexMatrix(rank, 2 * rank);

    // Setting the temp matrix
    for (int i = 0; i < rank; i++) {
        for (int j = 0; j < 2 * rank; j++) {
            if (j < rank)
                tempMatrix.set(i, j, A.get(i, j));
            if (j == (i + rank))
                tempMatrix.set(i, j, ComplexNum(1, 0));
        }
    }

    for (int i = 0; i < rank; i++) {
        tempMatrix.set(i, i + rank, ComplexNum(1, 0));
    }
}
/// @brief Calculates the Gauss-Jordan inverse of the matrix.
/// @return The calculated Gauss-Jordan inverse matrix.
ComplexMatrix GaussJordanInverse::calculateGaussJordanInverse() {
    for (int i = 0; i < rank; i++) {
        bool swapped = false;
        while (tempMatrix.get(i, i) == ComplexNum(0, 0)) {
            tempMatrix.swapRows(i, i + 1);
            swapped = true;
        }
        if (swapped) {
            i = std::max(0, i - 1);
            continue;
        }
        if (tempMatrix.get(i, i) == ComplexNum(0, 0))
            throw std::exception(); // Checking nulls on a principal diagonal

        for (int j = 0; j < rank; j++) {
            if (i != j) {
                ComplexNum temp = tempMatrix.get(j, i) / tempMatrix.get(i, i);

                for (int k = 0; k < 2 * rank; k++) {
                    tempMatrix.set(j, k, tempMatrix.get(j, k) - tempMatrix.get(i, k) * temp);
                }
            }
        }
    }

    for (int i = 0; i < rank; i++) {
        ComplexNum temp = tempMatrix.get(i, i);
        for (int j = 0; j < 2 * rank; j++) {
            tempMatrix.set(i, j, tempMatrix.get(i, j) / temp);
        }
    }

    ComplexMatrix resMatrix(rank, rank);

    for (int i = 0; i < rank; i++) {
        for (int j = 0; j < rank; j++) {
            resMatrix.set(i, j, tempMatrix.get(i, j + rank));
        }
    }

    return resMatrix;
}
