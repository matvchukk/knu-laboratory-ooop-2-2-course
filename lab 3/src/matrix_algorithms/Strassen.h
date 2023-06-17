#pragma once
#include <iostream>
#include "ComplexMatrix.h"

class Strassen {
public:
    static ComplexMatrix* regularMult(ComplexMatrix* a, ComplexMatrix* b);

    static ComplexMatrix* strassenRecursion(ComplexMatrix* a, ComplexMatrix* b);

    static ComplexMatrix* strassenMultiply(ComplexMatrix* a, ComplexMatrix* b);
};
