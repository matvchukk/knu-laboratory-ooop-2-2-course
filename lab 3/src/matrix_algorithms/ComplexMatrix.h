#pragma once
#include "ComplexNum.h"
#include <cassert>
/// @brief Class representing a complex matrix.
class ComplexMatrix
{
private:
    ComplexNum** matrix; ///< Pointer to the matrix data
    int columns; ///< Number of columns in the matrix
    int rows; ///< Number of rows in the matrix
public:
    /// @brief Default constructor.
    ComplexMatrix();    

    /// @brief Parameterized constructor.
    /// @param rows Number of rows in the matrix.
    /// @param columns Number of columns in the matrix.
    ComplexMatrix(unsigned int rows, unsigned int columns);

    /// @brief Copy constructor.
    /// @param copy The matrix to copy.
    ComplexMatrix(const ComplexMatrix& copy);

    /// @brief Destructor.
    ~ComplexMatrix();

    /// @brief Automatically generate matrix elements within specified ranges.
    /// @param min_real Minimum value for the real part.
    /// @param max_real Maximum value for the real part.
    /// @param min_imag Minimum value for the imaginary part.
    /// @param max_imag Maximum value for the imaginary part.
    void auto_gen(int min_real, int max_real, int min_imag, int max_imag);

    /// @brief Get the number of columns in the matrix.
    /// @return Number of columns.
    int getColumns();

    /// @brief Get the number of rows in the matrix.
    /// @return Number of rows.
    int getRows();

    /// @brief Set the value of a matrix element.
    /// @param i Row index.
    /// @param j Column index.
    /// @param real Real part of the complex number.
    /// @param imag Imaginary part of the complex number.
    void set(unsigned int i, unsigned int j, double real, double imag);

    /// @brief Set the value of a matrix element.
    /// @param i Row index.
    /// @param j Column index.
    /// @param num Complex number.
    void set(unsigned int i, unsigned int j, ComplexNum num);

    /// @brief Set the values of a column in the matrix.
    /// @param j Column index.
    /// @param num Array of complex numbers.
    void setColumn(int j, ComplexNum* num);

    /// @brief Set the values of a row in the matrix.
    /// @param i Row index.
    /// @param num Array of complex numbers.
    void setRow(int i, ComplexNum* num);

    /// @brief Get the value of a matrix element.
    /// @param i Row index.
    /// @param j Column index.
    /// @return Complex number at the specified position.
    ComplexNum get(unsigned int i, unsigned int j);

    /// @brief Print the matrix elements.
    void print();

    /// @brief Swap two rows in the matrix.
    /// @param row1 Index of the first row.
    /// @param row2 Index of the second row.
    void swapRows(int row1, int row2);

    /// @brief Get the rank of the matrix.
    /// @return Rank of the matrix.
    int getRank();

    /// @brief Assignment operator.
    /// @param copy The matrix to copy.
    /// @return Reference to the assigned matrix.
    ComplexMatrix& operator =(const ComplexMatrix& copy);

    /// @brief Addition operator for matrices.
    /// @param other The matrix to add.
    /// @return Resulting matrix after addition.
    ComplexMatrix operator +(const ComplexMatrix& other) const;

    /// @brief Multiplication operator for matrices.
    /// @param other The matrix to multiply.
    /// @return Resulting matrix after multiplication.
    ComplexMatrix operator *(const ComplexMatrix& other) const;

    /// @brief Equality comparison operator for matrices.
    /// @param other The matrix to compare.
    /// @return True if the matrices are equal, false otherwise.
    bool operator ==(const ComplexMatrix& other) const;

    /// @brief Subtraction operator for matrices.
    /// @param other The matrix to subtract.
    /// @return Resulting matrix after subtraction.
    ComplexMatrix operator -(const ComplexMatrix& other) const;
};
