#include "ParallelLUInverse.h"
#include <mutex>
/// @brief Performs LU decomposition of the input matrix in parallel.
/// @param a The input matrix to decompose.
/// @param l The lower triangular matrix (output).
/// @param u The upper triangular matrix (output).
/// @return True if the decomposition is successful, false otherwise.
bool ParallelLUInverse::parallelLUDecomposition(ComplexMatrix inputMatrix, ComplexMatrix& l, ComplexMatrix& u)
{
    if (inputMatrix.getColumns() != inputMatrix.getRows())
        return false;

    int size = inputMatrix.getColumns();

    l = ComplexMatrix(size, size);
    u = ComplexMatrix(size, size);

    ComplexNum zero;
    ComplexNum one(1);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            l.set(i, j, zero);
            u.set(i, j, zero);
        }
        l.set(i, i, one);
    }

    std::vector<std::mutex> lMutexes(size * size);
    std::vector<std::mutex> uMutexes(size * size);

    std::vector<std::thread> threads;
    for (int i = 0; i < size; i++)
    {
        threads.push_back(std::thread([&](int row) {
            for (int j = 0; j < size; j++)
            {
                ComplexNum toAdd = inputMatrix.get(row, j);
                if (row <= j)
                {
                    for (int k = 0; k <= row - 1; k++)
                        toAdd = toAdd - (l.get(row, k) * u.get(k, j));

                    // Блокування м'ютексу перед зміною значення у l
                    lMutexes[row * size + j].lock();
                    u.set(row, j, toAdd);
                    lMutexes[row * size + j].unlock();
                }
                else
                {
                    ComplexNum divider = u.get(j, j);
                    if (std::isnan(divider.getReal()) || std::isnan(divider.getImag()))
                        return;

                    for (int k = 0; k <= j - 1; k++)
                        toAdd = toAdd - (l.get(row, k) * u.get(k, j));

                    // Блокування м'ютексу перед зміною значення у u
                    uMutexes[row * size + j].lock();
                    toAdd = toAdd / divider;
                    uMutexes[row * size + j].unlock();

                    // Блокування м'ютексу перед зміною значення у l
                    lMutexes[row * size + j].lock();
                    l.set(row, j, toAdd);
                    lMutexes[row * size + j].unlock();
                }
            }
            }, i));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return true;
}
/// @brief Creates an empty complex number array of size n.
/// @param n The size of the array.
/// @return Pointer to the created array.
ComplexNum* ParallelLUInverse::createEmpty(int size)
{
    ComplexNum* result = new ComplexNum[size];
    for (int i = 0; i < size; i++)
        result[i] = ComplexNum();
    return result;
}
/// @brief Performs forward substitution for solving a system of equations with a lower triangular matrix.
/// @param l The lower triangular matrix.
/// @param vector The input vector.
/// @param n The size of the matrix and vector.
/// @return Pointer to the solution vector.
ComplexNum* ParallelLUInverse::forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int size)
{
    ComplexNum* result = new ComplexNum[size];
    for (int i = 0; i < size; i++)
    {
        ComplexNum toAdd = vector[i];
        for (int j = 0; j < size - 1; j++)
            toAdd = toAdd - l.get(i, j) * result[j];
        toAdd = toAdd / l.get(i, i);
        result[i] = toAdd;
    }
    return result;
}
/// @brief Performs back substitution for solving a system of equations with an upper triangular matrix.
/// @param u The upper triangular matrix.
/// @param vector The input vector.
/// @param n The size of the matrix and vector.
/// @return Pointer to the solution vector.
ComplexNum* ParallelLUInverse::backSubstitution(ComplexMatrix u, ComplexNum* vector, int size)
{
    ComplexNum* result = new ComplexNum[size];
    for (int i = size - 1; i >= 0; i--)
    {
        ComplexNum toAdd = vector[i];
        for (int j = i + 1; j < size; j++)
            toAdd = toAdd - u.get(i, j) * result[j];
        toAdd = toAdd / u.get(i, i);
        result[i] = toAdd;
    }
    return result;
}
/// @brief Calculates the inverse of the input matrix using LU decomposition in parallel.
/// @param a The input matrix.
/// @return The calculated inverse matrix.
ComplexMatrix ParallelLUInverse::calculateParallelLUInverse(ComplexMatrix inputMatrix)
{
    ComplexMatrix l(0, 0);
    ComplexMatrix u(0, 0);

    if (!parallelLUDecomposition(inputMatrix, l, u))
        return ComplexMatrix(0, 0);

    int size = inputMatrix.getColumns();
    ComplexMatrix result(size, size);

    for (int i = 0; i < size; i++)
    {
        ComplexNum* unitVector = createEmpty(size);
        unitVector[i] = ComplexNum(1, 0);
        ComplexNum* lVector = forwardSubstitution(l, unitVector, size);
        ComplexNum* uVector = backSubstitution(u, lVector, size);
        result.setColumn(i, uVector);
        delete[] unitVector;
        delete[] lVector;
        delete[] uVector;
    }

    return result;
}

