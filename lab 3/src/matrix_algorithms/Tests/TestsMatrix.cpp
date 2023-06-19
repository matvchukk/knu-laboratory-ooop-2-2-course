#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../ComplexMatrix.h"
#include "../MatrixInverseFactory.h"
#include "../TimeMatrixInverseFactory.h"

bool isIdentityMatrix(ComplexMatrix& matrix) {
    int rows = matrix.getRows();
    int cols = matrix.getColumns();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ComplexNum value = matrix.get(i, j);
            ComplexNum expectedValue = (i == j) ? ComplexNum(1, 0) : ComplexNum(0, 0); 

            if (value != expectedValue) {
                return false;
            }
        }
    }

    return true;
}

TEST_CASE("Matrix Inverse Algorithms") {
    SUBCASE("LU Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, 1);
        A.set(0, 1, 2);
        A.set(1, 0, 3);
        A.set(1, 1, 4);

        ComplexMatrix expectedInverse(2, 2);
        expectedInverse.set(0, 0, -2);
        expectedInverse.set(0, 1, 1);
        expectedInverse.set(1, 0, 1.5);
        expectedInverse.set(1, 1, -0.5);

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        CHECK(inverse == expectedInverse);
    }

    SUBCASE("Parallel LU Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, 1);
        A.set(0, 1, 2);
        A.set(1, 0, 3);
        A.set(1, 1, 4);

        ComplexMatrix expectedInverse(2, 2);
        expectedInverse.set(0, 0, -2);
        expectedInverse.set(0, 1, 1);
        expectedInverse.set(1, 0, 1.5);
        expectedInverse.set(1, 1, -0.5);

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        CHECK(inverse == expectedInverse);
    }

    SUBCASE("Gauss-Jordan Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, 1);
        A.set(0, 1, 2);
        A.set(1, 0, 3);
        A.set(1, 1, 4);

        ComplexMatrix expectedInverse(2, 2);
        expectedInverse.set(0, 0, -2);
        expectedInverse.set(0, 1, 1);
        expectedInverse.set(1, 0, 1.5);
        expectedInverse.set(1, 1, -0.5);

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::GaussJordan);
        CHECK(inverse == expectedInverse);
    }

    SUBCASE("Parallel Gauss-Jordan Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, 1);
        A.set(0, 1, 2);
        A.set(1, 0, 3);
        A.set(1, 1, 4);

        ComplexMatrix expectedInverse(2, 2);
        expectedInverse.set(0, 0, -2);
        expectedInverse.set(0, 1, 1);
        expectedInverse.set(1, 0, 1.5);
        expectedInverse.set(1, 1, -0.5);

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::ParallelGaussJordan);
        CHECK(inverse == expectedInverse);
    }
}
TEST_CASE("Matrix Inverse Algorithms with complex values") {
    SUBCASE("LU Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));
        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        CHECK(isIdentity);
    }

    SUBCASE("Parallel LU Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));
        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        CHECK(isIdentity);
    }

    SUBCASE("Gauss-Jordan Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));
        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::GaussJordan);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        CHECK(isIdentity);
    }

    SUBCASE("Parallel Gauss-Jordan Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));
        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::ParallelGaussJordan);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        CHECK(isIdentity);
    }
}

TEST_CASE("Matrix Inverse Algorithms with complex values on incorrect data") {
    SUBCASE("LU Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, ComplexNum(1, 0));
        A.set(0, 1, ComplexNum(2, 0));
        A.set(1, 0, ComplexNum(3, 0));
        A.set(1, 1, ComplexNum(4, 0));

        ComplexMatrix unexpectedInverse(2, 2);
        unexpectedInverse.set(0, 0, ComplexNum(1, 0));
        unexpectedInverse.set(0, 1, ComplexNum(2, 0));
        unexpectedInverse.set(1, 0, ComplexNum(3, 0));
        unexpectedInverse.set(1, 1, ComplexNum(5, 0));

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        bool matricesAreEqual = (inverse == unexpectedInverse);
        CHECK_FALSE(matricesAreEqual);
    }

    SUBCASE("Parallel LU Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, ComplexNum(1, 0));
        A.set(0, 1, ComplexNum(2, 0));
        A.set(1, 0, ComplexNum(3, 0));
        A.set(1, 1, ComplexNum(4, 0));

        ComplexMatrix unexpectedInverse(2, 2);
        unexpectedInverse.set(0, 0, ComplexNum(1, 0));
        unexpectedInverse.set(0, 1, ComplexNum(2, 0));
        unexpectedInverse.set(1, 0, ComplexNum(3, 0));
        unexpectedInverse.set(1, 1, ComplexNum(5, 0));

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::LU);
        bool matricesAreEqual = (inverse == unexpectedInverse);
        CHECK_FALSE(matricesAreEqual);
    }

    SUBCASE("Gauss-Jordan Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, ComplexNum(1, 0));
        A.set(0, 1, ComplexNum(2, 0));
        A.set(1, 0, ComplexNum(3, 0));
        A.set(1, 1, ComplexNum(4, 0));

        ComplexMatrix unexpectedInverse(2, 2);
        unexpectedInverse.set(0, 0, ComplexNum(1, 0));
        unexpectedInverse.set(0, 1, ComplexNum(2, 0));
        unexpectedInverse.set(1, 0, ComplexNum(3, 0));
        unexpectedInverse.set(1, 1, ComplexNum(5, 0));

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::GaussJordan);
        bool matricesAreEqual = (inverse == unexpectedInverse);
        CHECK_FALSE(matricesAreEqual);
    }

    SUBCASE("Parallel Gauss-Jordan Inverse") {
        ComplexMatrix A(2, 2);
        A.set(0, 0, ComplexNum(1, 0));
        A.set(0, 1, ComplexNum(2, 0));
        A.set(1, 0, ComplexNum(3, 0));
        A.set(1, 1, ComplexNum(4, 0));

        ComplexMatrix unexpectedInverse(2, 2);
        unexpectedInverse.set(0, 0, ComplexNum(1, 0));
        unexpectedInverse.set(0, 1, ComplexNum(2, 0));
        unexpectedInverse.set(1, 0, ComplexNum(3, 0));
        unexpectedInverse.set(1, 1, ComplexNum(5, 0));

        ComplexMatrix inverse = MatrixInverseFactory::calculateInverse(A, InverseAlgorithm::ParallelGaussJordan);
        bool matricesAreEqual = (inverse == unexpectedInverse);
        CHECK_FALSE(matricesAreEqual);
    }
}

TEST_CASE("Matrix Inverse Algorithms with complex values with time measurement") {
    SUBCASE("LU Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));

        MatrixInverseFactory factory;
        TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::LU);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        ComplexMatrix inverse = timeFactory.calculateInverse(A);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        std::cout << "LU Inverse Execution Time: " << duration.count() << " seconds" << std::endl;

        CHECK(isIdentity);
    }

    SUBCASE("Parallel LU Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));

        MatrixInverseFactory factory;
        TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::LU);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        ComplexMatrix inverse = timeFactory.calculateInverse(A);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        std::cout << "Parallel LU Inverse Execution Time: " << duration.count() << " seconds" << std::endl;

        CHECK(isIdentity);
    }

    SUBCASE("Gauss-Jordan Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));

        MatrixInverseFactory factory;
        TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::GaussJordan);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        ComplexMatrix inverse = timeFactory.calculateInverse(A);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        std::cout << "Gauss-Jordan Inverse Execution Time: " << duration.count() << " seconds" << std::endl;

        CHECK(isIdentity);
    }

    SUBCASE("Parallel Gauss-Jordan Inverse") {
        ComplexMatrix A(4, 4);
        A.set(0, 0, ComplexNum(26, 22));
        A.set(0, 1, ComplexNum(16, 49));
        A.set(0, 2, ComplexNum(14, 36));
        A.set(0, 3, ComplexNum(42, 28));
        A.set(1, 0, ComplexNum(40, 5));
        A.set(1, 1, ComplexNum(30, 37));
        A.set(1, 2, ComplexNum(42, 46));
        A.set(1, 3, ComplexNum(48, 39));
        A.set(2, 0, ComplexNum(22, 10));
        A.set(2, 1, ComplexNum(25, 20));
        A.set(2, 2, ComplexNum(31, 15));
        A.set(2, 3, ComplexNum(37, 41));
        A.set(3, 0, ComplexNum(45, 43));
        A.set(3, 1, ComplexNum(39, 39));
        A.set(3, 2, ComplexNum(40, 22));
        A.set(3, 3, ComplexNum(21, 18));

        MatrixInverseFactory factory;
        TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::ParallelGaussJordan);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        ComplexMatrix inverse = timeFactory.calculateInverse(A);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        ComplexMatrix product = A * inverse;
        bool isIdentity = isIdentityMatrix(product);
        std::cout << "Parallel Gauss-Jordan Inverse Execution Time: " << duration.count() << " seconds" << std::endl;

        CHECK(isIdentity);
    }

}

TEST_CASE("Matrix Inverse Algorithms with complex values with random values and average time measurement") {
    SUBCASE("LU Inverse") {
        srand(static_cast<unsigned int>(time(0)));
        std::vector<double> executionTimes;
        for (int i = 0; i < 8; ++i) {
            ComplexMatrix A(4, 4);
            A.auto_gen(50000, 500000, 50000, 500000);
            MatrixInverseFactory factory;
            TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::LU);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ComplexMatrix inverse = timeFactory.calculateInverse(A);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
            ComplexMatrix product = A * inverse;
            bool isIdentity = isIdentityMatrix(product);
            std::cout << "Matrix " << i + 1 << " LU Inverse Execution Time: " << duration.count() << " seconds" << std::endl;
            A.print();
            product.print();
            executionTimes.push_back(duration.count());
            CHECK(isIdentity);
        }
        double totalExecutionTime = 0;
        for (double time : executionTimes) {
            totalExecutionTime += time;
        }
        double averageExecutionTime = totalExecutionTime / executionTimes.size();
        std::cout << "Average LU Inverse Execution Time: " << averageExecutionTime << " seconds" << std::endl;
    }
    SUBCASE("Parallel LU Inverse") {
        srand(static_cast<unsigned int>(time(0)));
        std::vector<double> executionTimes;
        for (int i = 0; i < 8; ++i) {
            ComplexMatrix A(4, 4);
            A.auto_gen(50000, 500000, 50000, 500000);
            MatrixInverseFactory factory;
            TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::LU);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ComplexMatrix inverse = timeFactory.calculateInverse(A);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
            ComplexMatrix product = A * inverse;
            bool isIdentity = isIdentityMatrix(product);
            std::cout << "Matrix " << i + 1 << " Parallel LU Inverse Execution Time: " << duration.count() << " seconds" << std::endl;
            A.print();
            product.print();
            executionTimes.push_back(duration.count());
            CHECK(isIdentity);
        }
        double totalExecutionTime = 0;
        for (double time : executionTimes) {
            totalExecutionTime += time;
        }
        double averageExecutionTime = totalExecutionTime / executionTimes.size();
        std::cout << "Average Parallel LU Inverse Execution Time: " << averageExecutionTime << " seconds" << std::endl;
    }
    SUBCASE("Gauss-Jordan Inverse") {
        srand(static_cast<unsigned int>(time(0)));
        std::vector<double> executionTimes;
        for (int i = 0; i < 8; ++i) {
            ComplexMatrix A(4, 4);
            A.auto_gen(50000, 500000, 50000, 500000);
            MatrixInverseFactory factory;
            TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::GaussJordan);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ComplexMatrix inverse = timeFactory.calculateInverse(A);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
            ComplexMatrix product = A * inverse;
            bool isIdentity = isIdentityMatrix(product);
            std::cout << "Matrix " << i + 1 << " Gauss-Jordan Inverse Execution Time: " << duration.count() << " seconds" << std::endl;
            A.print();
            product.print();
            executionTimes.push_back(duration.count());
            CHECK(isIdentity);
        }
        double totalExecutionTime = 0;
        for (double time : executionTimes) {
            totalExecutionTime += time;
        }
        double averageExecutionTime = totalExecutionTime / executionTimes.size();
        std::cout << "Average Gauss-Jordan Inverse Execution Time: " << averageExecutionTime << " seconds" << std::endl;
    }
    SUBCASE("Parallel Gauss-Jordan Inverse") {
        srand(static_cast<unsigned int>(time(0)));
        std::vector<double> executionTimes;
        for (int i = 0; i < 8; ++i) {
            ComplexMatrix A(4, 4);
            A.auto_gen(50000, 500000, 50000, 500000);
            MatrixInverseFactory factory;
            TimeMatrixInverseFactory timeFactory(factory, InverseAlgorithm::ParallelGaussJordan);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            ComplexMatrix inverse = timeFactory.calculateInverse(A);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
            ComplexMatrix product = A * inverse;
            bool isIdentity = isIdentityMatrix(product);
            std::cout << "Matrix " << i + 1 << " Parallel Gauss-Jordan Inverse Execution Time: " << duration.count() << " seconds" << std::endl;
            A.print();
            product.print();
            executionTimes.push_back(duration.count());
            CHECK(isIdentity);
        }
        double totalExecutionTime = 0;
        for (double time : executionTimes) {
            totalExecutionTime += time;
        }
        double averageExecutionTime = totalExecutionTime / executionTimes.size();
        std::cout << "Average Parallel Gauss-Jordan Inverse Execution Time: " << averageExecutionTime << " seconds" << std::endl;
    }
}
