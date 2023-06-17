#include "ComplexNum.h"

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

void ComplexNum::operator=(const ComplexNum& c1) {
    this->real = c1.real;
    this->imag = c1.imag;
}

ComplexNum ComplexNum::operator +(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real + c1.real;
    new_num.imag = this->imag + c1.imag;
    return new_num;
}

ComplexNum ComplexNum::operator -(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real - c1.real;
    new_num.imag = this->imag - c1.imag;
    return new_num;
}

ComplexNum ComplexNum::operator *(const ComplexNum& c1) const {
    ComplexNum new_num;
    new_num.real = this->real * c1.real - this->imag * c1.imag;
    new_num.imag = this->imag * c1.real + this->real * c1.imag;
    return new_num;
}

ComplexNum ComplexNum::operator /(const ComplexNum& c1) const {
    double div = c1.real * c1.real + c1.imag * c1.imag;
    ComplexNum new_num;
    new_num.real = this->real * c1.real + this->imag * c1.imag;
    new_num.real /= div;
    new_num.imag = this->imag * c1.real - this->real * c1.imag;
    new_num.imag /= div;
    return new_num;
}

bool ComplexNum::operator ==(const ComplexNum& c1) const {
    if (fabs(this->real - c1.real) < EPSILON && fabs(this->imag - c1.imag) < EPSILON)
        return true;
    return false;
}

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
