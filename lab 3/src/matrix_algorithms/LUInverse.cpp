#include "LUInverse.h"

bool LUInverse::LUDecomposition(ComplexMatrix inputMatrix, ComplexMatrix& l, ComplexMatrix& u)
{
    if (inputMatrix.getColumns() != inputMatrix.getRows())
        return false;

    int n = inputMatrix.getColumns();

    l = ComplexMatrix(n, n);
    u = ComplexMatrix(n, n);

    ComplexNum zero;
    ComplexNum one(1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            l.set(i, j, zero);
            u.set(i, j, zero);
        }
        l.set(i, i, one);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ComplexNum toAdd = inputMatrix.get(i, j);
            if (i <= j)
            {
                for (int k = 0; k <= i - 1; k++)
                    toAdd = toAdd - (l.get(i, k) * u.get(k, j));
                u.set(i, j, toAdd);
            }
            else
            {
                ComplexNum divider = u.get(j, j);
                if (divider.getReal() == 0 && divider.getImag() == 0)
                    return false;
                for (int k = 0; k <= j - 1; k++)
                    toAdd = toAdd - (l.get(i, k) * u.get(k, j));
                toAdd = toAdd / divider;
                l.set(i, j, toAdd);
            }
        }
    }

    return true;
}

ComplexNum* LUInverse::createEmpty(int size)
{
    ComplexNum* result = new ComplexNum[size];
    for (int i = 0; i < size; i++)
        result[i] = ComplexNum();
    return result;
}

ComplexNum* LUInverse::forwardSubstitution(ComplexMatrix l, ComplexNum* vector, int size)
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

ComplexNum* LUInverse::backSubstitution(ComplexMatrix u, ComplexNum* vector, int size)
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

ComplexMatrix LUInverse::calculateLUInverse(ComplexMatrix inputMatrix)
{
    ComplexMatrix l(0, 0);
    ComplexMatrix u(0, 0);

    if (!LUDecomposition(inputMatrix, l, u))
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
