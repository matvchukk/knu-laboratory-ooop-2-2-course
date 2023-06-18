#include "ComplexNum.h"
/// @brief Constructs a ComplexNum object.
/// @param real The real part of the complex number 
/// @param imag The imaginary part of the complex number 
ComplexNum::ComplexNum(double real, double imag) {
    this->real = real;
    this->imag = imag;
}

double ComplexNum::getReal() {
    return this->real;
}

double ComplexNum::getImag() {
    return this->imag;
}

bool ComplexNum::isNull() {
    if (this->real == 0.0 && this->imag == 0.0)
        return true;
    return false;
}

/// @brief Assigns the value of another complex number to this complex number.
/// @param c1 The complex number to be assigned.
void ComplexNum::operator=(const ComplexNum& c1) {
    this->real = c1.real;
    this->imag = c1.imag;
}
/// @brief Adds another complex number to this complex number.
/// @param c1 The complex number to be added.
/// @return The resulting complex number after addition.
ComplexNum ComplexNum::operator +(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real + c1.real;
    new_num.imag = this->imag + c1.imag;
    return new_num;
}
/// @brief Subtracts another complex number from this complex number.
/// @param c1 The complex number to be subtracted.
/// @return The resulting complex number after subtraction.
ComplexNum ComplexNum::operator -(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real - c1.real;
    new_num.imag = this->imag - c1.imag;
    return new_num;
}
/// @brief Multiplies this complex number by another complex number.
/// @param c1 The complex number to be multiplied by.
/// @return The resulting complex number after multiplication.
ComplexNum ComplexNum::operator *(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real * c1.real - this->imag * c1.imag;
    new_num.imag = this->imag * c1.real + this->real * c1.imag;
    return new_num;
}
/// @brief Divides this complex number by another complex number.
/// @param c1 The complex number to be divided by.
/// @return The resulting complex number after division.
ComplexNum ComplexNum::operator /(const ComplexNum& c1) const {
    double div = c1.real * c1.real + c1.imag * c1.imag;
    ComplexNum new_num;
    new_num.real = this->real * c1.real + this->imag * c1.imag;
    new_num.real /= div;
    new_num.imag = this->imag * c1.real - this->real * c1.imag;
    new_num.imag /= div;
    return new_num;
}
/// @brief Checks if this complex number is equal to another complex number.
/// @param c1 The complex number to be compared with.
/// @return True if the complex numbers are equal, false otherwise.
bool ComplexNum::operator ==(const ComplexNum& c1) const {
    if (fabs(this->real - c1.real) < EPSILON && fabs(this->imag - c1.imag) < EPSILON)
        return true;
    return false;
}
/// @brief Checks if this complex number is not equal to another complex number.
/// @param c1 The complex number to be compared with.
/// @return True if the complex numbers are not equal, false otherwise.
bool ComplexNum::operator !=(const ComplexNum& c1) const {
    if (fabs(this->real - c1.real) < EPSILON && fabs(this->imag - c1.imag) < EPSILON)
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const ComplexNum& c) {
    if (c.real) {
        os << std::setprecision(3) << c.real;
    }
    if (c.imag >= 0) {
        os << "+" << std::setprecision(3) << c.imag << "i";
    }
    else {
        os << std::setprecision(3) << c.imag << "i";
    }
    return os;
}
