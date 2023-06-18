#include "Strassen.h"
/// @brief Performs matrix multiplication using the regular algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @return Pointer to the resulting matrix.
ComplexMatrix* Strassen::regularMult(ComplexMatrix* a, ComplexMatrix* b) {
    ComplexMatrix* result = new ComplexMatrix(a->getRows(), b->getColumns());
    for (int i = 0; i < a->getRows(); i++) {
        for (int j = 0; j < b->getColumns(); j++) {
            for (int k = 0; k < b->getRows(); k++) {
                result->set(i, j, result->get(i, j) + a->get(i, k) * b->get(k, j));
            }
        }
    }
    return result;
}
/// @brief Performs the recursive step of the Strassen algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @return Pointer to the resulting matrix.
ComplexMatrix* Strassen::strassenRecursion(ComplexMatrix* a, ComplexMatrix* b) {
    int n = a->getColumns();
    int m = a->getRows();
    int q = b->getColumns();
    if (n <= 8 || m <= 8 || q <= 8) {
        return regularMult(a, b);
    }
    int newN = n / 2 + n % 2;
    int newM = m / 2 + m % 2;
    int newQ = q / 2 + q % 2;
    ComplexMatrix a11(newM, newN);
    ComplexMatrix a12(newM, newN);
    ComplexMatrix a21(newM, newN);
    ComplexMatrix a22(newM, newN);

    for (int i = 0; i < newM; i++) {
        for (int j = 0; j < newN; j++) {
            a11.set(i, j, a->get(i, j));
            a12.set(i, j, ((j + newN) < n) ? a->get(i, j + newN) : ComplexNum(0, 0));
            a21.set(i, j, ((i + newM) < m) ? a->get(i + newM, j) : ComplexNum(0, 0));
            a22.set(i, j, ((i + newM) < m && (j + newN) < n) ? a->get(i + newM, j + newN) : ComplexNum(0, 0));
        }
    }

    ComplexMatrix b11(newN, newQ);
    ComplexMatrix b12(newN, newQ);
    ComplexMatrix b21(newN, newQ);
    ComplexMatrix b22(newN, newQ);

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

    ComplexMatrix* m1 = strassenRecursion(&d1, &d2);
    ComplexMatrix* m2 = strassenRecursion(&d3, &b11);
    ComplexMatrix* m3 = strassenRecursion(&a11, &d4);
    ComplexMatrix* m4 = strassenRecursion(&a22, &d5);
    ComplexMatrix* m5 = strassenRecursion(&d6, &(b22));
    ComplexMatrix* m6 = strassenRecursion(&d7, &d8);
    ComplexMatrix* m7 = strassenRecursion(&d9, &d10);

    ComplexMatrix r1 = *m1 + *m4 - *m5 + *m7;
    ComplexMatrix r2 = *m3 + *m5;
    ComplexMatrix r3 = *m2 + *m4;
    ComplexMatrix r4 = *m1 - *m2 + *m3 + *m6;

    ComplexMatrix* result = new ComplexMatrix(m, q);
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

    delete m1;
    delete m2;
    delete m3;
    delete m4;
    delete m5;
    delete m6;
    delete m7;
    return result;
}
/// @brief Performs matrix multiplication using the Strassen algorithm.
/// @param a The first input matrix.
/// @param b The second input matrix.
/// @return Pointer to the resulting matrix.
ComplexMatrix* Strassen::strassenMultiply(ComplexMatrix* a, ComplexMatrix* b) {
    assert(a->getColumns() == b->getRows());
    if (a->getColumns() <= 8 || a->getRows() <= 8 || b->getColumns() <= 8) {
        return regularMult(a, b);
    }

    return strassenRecursion(a, b);
}
