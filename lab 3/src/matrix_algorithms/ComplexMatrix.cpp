#include "ComplexMatrix.h"
#include <iostream>

ComplexMatrix::ComplexMatrix() : matrix(nullptr), rows(0), columns(0) {}

ComplexMatrix::ComplexMatrix(unsigned int rows, unsigned int columns)
{
    matrix = new ComplexNum * [rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new ComplexNum[columns];
    }
    this->columns = columns;
    this->rows = rows;
}

ComplexMatrix::ComplexMatrix(const ComplexMatrix& copy)
{
    this->rows = copy.rows;
    this->columns = copy.columns;
    matrix = new ComplexNum * [rows];
    for (int i = 0; i < this->rows; i++)
        this->matrix[i] = new ComplexNum[copy.columns];

    for (int i = 0; i < copy.rows; i++)
        for (int j = 0; j < copy.columns; j++)
            this->matrix[i][j] = copy.matrix[i][j];
}

ComplexMatrix::~ComplexMatrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    this->rows = 0;
    this->columns = 0;
}

void ComplexMatrix::auto_gen(int min_real, int max_real, int min_imag, int max_imag)
{
    int span_real = abs(max_real - min_real) + 1;
    int span_imag = abs(max_imag - min_imag) + 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = ComplexNum(rand() % span_real + min_real, rand() % span_imag + min_imag);
        }
    }
}

int ComplexMatrix::getColumns()
{
    return columns;
}

int ComplexMatrix::getRows()
{
    return rows;
}

void ComplexMatrix::set(unsigned int i, unsigned int j, double real, double imag)
{
    assert(i < rows);
    assert(j < columns);
    matrix[i][j] = ComplexNum(real, imag);
}

void ComplexMatrix::set(unsigned int i, unsigned int j, ComplexNum num)
{
    assert(i < rows);
    assert(j < columns);
    matrix[i][j] = num;
}

void ComplexMatrix::setColumn(int j, ComplexNum* num)
{
    for (int i = 0; i < this->rows; i++)
        this->set(i, j, num[i]);
}

void ComplexMatrix::setRow(int i, ComplexNum* num)
{
    for (int j = 0; j < this->columns; j++)
        this->set(i, j, num[j]);
}

ComplexNum ComplexMatrix::get(unsigned int i, unsigned int j)
{
    assert(i < rows);
    assert(j < columns);
    return matrix[i][j];
}

void ComplexMatrix::print()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

void ComplexMatrix::swapRows(int row1, int row2)
{
    assert(row1 >= 0 && row1 < rows);
    assert(row2 >= 0 && row2 < columns);

    int col = this->getColumns();
    for (int i = 0; i < col; i++)
    {
        ComplexNum temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

int ComplexMatrix::getRank()
{
    ComplexMatrix complexMatrix = *this;

    int R = complexMatrix.getRows();
    int rank = complexMatrix.getColumns();

    for (int row = 0; row < rank; row++)
    {
        if (complexMatrix.get(row, row) != ComplexNum())
        {
            for (int col = 0; col < R; col++)
            {
                if (col != row)
                {
                    ComplexNum mult = complexMatrix.get(col, row) / complexMatrix.get(row, row);
                    for (int i = 0; i < rank; i++)
                        complexMatrix.set(col, i,
                            complexMatrix.get(col, i) - mult * complexMatrix.get(row, i));
                }
            }
        }
        else
        {
            bool reduce = true;

            for (int i = row + 1; i < R; i++)
            {
                if (complexMatrix.get(i, row) != ComplexNum())
                {
                    complexMatrix.swapRows(row, i);
                    reduce = false;
                    break;
                }
            }
            if (reduce)
            {
                rank--;
                for (int i = 0; i < R; i++)
                    complexMatrix.set(i, row, complexMatrix.get(i, rank));
            }

            row--;
        }
    }

    return rank;
}

ComplexMatrix& ComplexMatrix::operator =(const ComplexMatrix& copy)
{
    if (this != &copy)
    {
        for (int i = 0; i < this->rows; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;

        matrix = new ComplexNum * [copy.rows];
        this->rows = copy.rows;
        this->columns = copy.columns;
        for (int i = 0; i < copy.rows; i++)
            this->matrix[i] = new ComplexNum[copy.columns];

        for (int i = 0; i < copy.rows; i++)
            for (int j = 0; j < copy.columns; j++)
                this->matrix[i][j] = copy.matrix[i][j];
    }

    return *this;
}

ComplexMatrix ComplexMatrix::operator +(const ComplexMatrix& other) const
{
    assert(this->rows == other.rows && this->columns == other.columns);

    ComplexMatrix result(this->rows, this->columns);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            result.set(i, j, this->matrix[i][j] + other.matrix[i][j]);
        }
    }

    return result;
}

ComplexMatrix ComplexMatrix::operator *(const ComplexMatrix& other) const
{
    assert(this->columns == other.rows);

    ComplexMatrix result(this->rows, other.columns);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < other.columns; j++)
        {
            ComplexNum sum = ComplexNum();
            for (int k = 0; k < this->columns; k++)
            {
                sum = sum + (this->matrix[i][k] * other.matrix[k][j]);
            }
            result.set(i, j, sum);
        }
    }

    return result;
}

bool ComplexMatrix::operator ==(const ComplexMatrix& other) const
{
    if (this->rows != other.rows || this->columns != other.columns)
        return false;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (this->matrix[i][j] != other.matrix[i][j])
                return false;
        }
    }

    return true;
}

ComplexMatrix ComplexMatrix::operator -(const ComplexMatrix& other) const
{
    assert(this->rows == other.rows && this->columns == other.columns);

    ComplexMatrix result(this->rows, this->columns);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            result.set(i, j, this->matrix[i][j] - other.matrix[i][j]);
        }
    }

    return result;
}
