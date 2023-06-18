#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>

class ComplexNum
{
private:
    double real;
    double imag;

    constexpr static const double EPSILON = 1E-6;

public:

    ComplexNum(double real = 0.0, double imag = 0.0);

    double getReal();
    double getImag();
    bool isNull();

    void operator=(const ComplexNum& c1);
    ComplexNum operator +(const ComplexNum& c1) const;
    /*ComplexNum operator +=(const ComplexNum& ñ1) const;*/
    ComplexNum operator -(const ComplexNum& c1) const;
    ComplexNum operator *(const ComplexNum& c1) const;
    ComplexNum operator /(const ComplexNum& c1) const;
    bool operator ==(const ComplexNum& c1) const;
    bool operator !=(const ComplexNum& c1) const;

    friend std::ostream& operator<<(std::ostream& os, const ComplexNum& c);
};
