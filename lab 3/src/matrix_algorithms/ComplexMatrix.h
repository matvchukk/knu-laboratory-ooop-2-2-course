#pragma once
#include "ComplexNum.h"
#include <cassert>

class ComplexMatrix
{
private:
    ComplexNum** matrix;
    int columns;
    int rows;

public:
    ComplexMatrix();
    ComplexMatrix(unsigned int rows, unsigned int columns);
    ComplexMatrix(const ComplexMatrix& copy);
    ~ComplexMatrix();

    void auto_gen(int min_real, int max_real, int min_imag, int max_imag);
    int getColumns();
    int getRows();
    void set(unsigned int i, unsigned int j, double real, double imag);
    void set(unsigned int i, unsigned int j, ComplexNum num);
    void setColumn(int j, ComplexNum* num);
    void setRow(int i, ComplexNum* num);
    ComplexNum get(unsigned int i, unsigned int j);
    void print();
    void swapRows(int row1, int row2);
    int getRank();
    ComplexMatrix& operator =(const ComplexMatrix& copy);
    ComplexMatrix operator +(const ComplexMatrix& other) const;
    ComplexMatrix operator *(const ComplexMatrix& other) const;
    bool operator ==(const ComplexMatrix& other) const;
    ComplexMatrix operator -(const ComplexMatrix& other) const;
};
