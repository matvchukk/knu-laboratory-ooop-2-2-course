#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
/// @brief Represents a complex number with real and imaginary parts.
class ComplexNum
{
private:
    double real; ///< The real part of the complex number
    double imag; ///< The imaginary part of the complex number

    constexpr static const double EPSILON = 1E-6; ///< The epsilon value for comparing floating-point numbers

public:
    /// @brief Constructs a ComplexNum object.
    /// @param real The real part of the complex number (default: 0.0)
    /// @param imag The imaginary part of the complex number (default: 0.0)
    ComplexNum(double real = 0.0, double imag = 0.0);

    /// @brief Gets the real part of the complex number.
    /// @return The real part.
    double getReal();

    /// @brief Gets the imaginary part of the complex number.
    /// @return The imaginary part.
    double getImag();

    /// @brief Checks if the complex number is null (both real and imaginary parts are zero).
    /// @return True if the complex number is null, false otherwise.
    bool isNull();

    /// @brief Assigns the value of another complex number to this complex number.
    /// @param c1 The complex number to be assigned.
    void operator=(const ComplexNum& c1);

    /// @brief Adds another complex number to this complex number.
    /// @param c1 The complex number to be added.
    /// @return The resulting complex number after addition.
    ComplexNum operator +(const ComplexNum& c1) const;

    /// @brief Subtracts another complex number from this complex number.
    /// @param c1 The complex number to be subtracted.
    /// @return The resulting complex number after subtraction.
    ComplexNum operator -(const ComplexNum& c1) const;

    /// @brief Multiplies this complex number by another complex number.
    /// @param c1 The complex number to be multiplied by.
    /// @return The resulting complex number after multiplication.
    ComplexNum operator *(const ComplexNum& c1) const;

    /// @brief Divides this complex number by another complex number.
    /// @param c1 The complex number to be divided by.
    /// @return The resulting complex number after division.
    ComplexNum operator /(const ComplexNum& c1) const;

    /// @brief Checks if this complex number is equal to another complex number.
    /// @param c1 The complex number to be compared with.
    /// @return True if the complex numbers are equal, false otherwise.
    bool operator ==(const ComplexNum& c1) const;

    /// @brief Checks if this complex number is not equal to another complex number.
    /// @param c1 The complex number to be compared with.
    /// @return True if the complex numbers are not equal, false otherwise.
    bool operator !=(const ComplexNum& c1) const;


    friend std::ostream& operator<<(std::ostream& os, const ComplexNum& c);
};
