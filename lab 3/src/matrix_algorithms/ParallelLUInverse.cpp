#include "ParallelLUInverse.h"
#include <mutex>

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


ComplexNum* ParallelLUInverse::createEmpty(int size)
{
    ComplexNum* result = new ComplexNum[size];
    for (int i = 0; i < size; i++)
        result[i] = ComplexNum();
    return result;
}

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
//#include "ParallelLUInverse.h"
//
//ParallelLUInverse::ParallelLUInverse(ComplexMatrix matrix) {
//    A = matrix;
//    rank = A.getRows();
//    columns = A.getColumns();
//
//    assert(rank == columns);
//    assert(rank == A.getRank());
//
//    lMatrix = ComplexMatrix(rank, rank);
//    uMatrix = ComplexMatrix(rank, rank);
//}
//
//ComplexMatrix ParallelLUInverse::calculateParallelLUInverse(ComplexMatrix a) {
//    A = a;
//    rank = A.getRows();
//    columns = A.getColumns();
//
//    assert(rank == columns);
//    assert(rank == A.getRank());
//
//    if (!LUInverse::LUDecomposition(A, lMatrix, uMatrix))
//        return ComplexMatrix(0, 0);
//
//    ComplexMatrix result(rank, rank);
//    std::vector<std::thread> threads;
//    threads.reserve(rank);
//
//    for (int i = 0; i < rank; i++) {
//        threads.emplace_back([this, i, &result]() {
//            ComplexNum* unitVector = LUInverse::createEmpty(rank);
//            unitVector[i] = ComplexNum(1, 0);
//            ComplexNum* lVector = LUInverse::forwardSubstitution(lMatrix, unitVector, rank);
//            ComplexNum* uVector = LUInverse::backSubstitution(uMatrix, lVector, rank);
//            std::lock_guard<std::mutex> lock(mtx);
//            result.setColumn(i, uVector);
//            delete[] unitVector;
//            delete[] lVector;
//            delete[] uVector;
//            });
//    }
//
//    for (std::thread& thread : threads) {
//        thread.join();
//    }
//
//    return result;
//}
