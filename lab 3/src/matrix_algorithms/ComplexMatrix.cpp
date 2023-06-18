#include "ComplexMatrix.h"
#include <iostream>

ComplexMatrix::ComplexMatrix() : matrix(nullptr), rows(0), columns(0) {}
/// @brief Parameterized constructor.
/// @param rows Number of rows in the matrix.
/// @param columns Number of columns in the matrix.
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
/// @brief Copy constructor.
/// @param copy The matrix to copy.
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
/// @brief Destructor.
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
/// @brief Automatically generate matrix elements within specified ranges.
/// @param min_real Minimum value for the real part.
/// @param max_real Maximum value for the real part.
/// @param min_imag Minimum value for the imaginary part.
/// @param max_imag Maximum value for the imaginary part.
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
/// @brief Get the number of columns in the matrix.
/// @return Number of columns.
int ComplexMatrix::getColumns()
{
    return columns;
}
/// @brief Get the number of rows in the matrix.
/// @return Number of rows.
int ComplexMatrix::getRows()
{
    return rows;
}
/// @brief Set the value of a matrix element.
/// @param i Row index.
/// @param j Column index.
/// @param real Real part of the complex number.
/// @param imag Imaginary part of the complex number.
void ComplexMatrix::set(unsigned int i, unsigned int j, double real, double imag)
{
    assert(i < rows);
    assert(j < columns);
    matrix[i][j] = ComplexNum(real, imag);
}
/// @brief Set the value of a matrix element.
/// @param i Row index.
/// @param j Column index.
/// @param num Complex number.
void ComplexMatrix::set(unsigned int i, unsigned int j, ComplexNum num)
{
    assert(i < rows);
    assert(j < columns);
    matrix[i][j] = num;
}
/// @brief Set the values of a column in the matrix.
/// @param j Column index.
/// @param num Array of complex numbers.
void ComplexMatrix::setColumn(int j, ComplexNum* num)
{
    for (int i = 0; i < this->rows; i++)
        this->set(i, j, num[i]);
}
/// @brief Set the values of a row in the matrix.
/// @param i Row index.
/// @param num Array of complex numbers.
void ComplexMatrix::setRow(int i, ComplexNum* num)
{
    for (int j = 0; j < this->columns; j++)
        this->set(i, j, num[j]);
}
/// @brief Get the value of a matrix element.
/// @param i Row index.
/// @param j Column index.
/// @return Complex number at the specified position.
ComplexNum ComplexMatrix::get(unsigned int i, unsigned int j)
{
    assert(i < rows);
    assert(j < columns);
    return matrix[i][j];
}
/// @brief Print the matrix elements.
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
/// @brief Swap two rows in the matrix.
/// @param row1 Index of the first row.
/// @param row2 Index of the second row.
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
/// @brief Get the rank of the matrix.
/// @return Rank of the matrix.
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
/// @brief Assignment operator.
/// @param copy The matrix to copy.
/// @return Reference to the assigned matrix.
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
/// @brief Addition operator for matrices.
/// @param other The matrix to add.
/// @return Resulting matrix after addition.
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
/// @brief Multiplication operator for matrices.
/// @param other The matrix to multiply.
/// @return Resulting matrix after multiplication.
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
/// @brief Equality comparison operator for matrices.
/// @param other The matrix to compare.
/// @return True if the matrices are equal, false otherwise.
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
/// @brief Subtraction operator for matrices.
/// @param other The matrix to subtract.
/// @return Resulting matrix after subtraction.
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
