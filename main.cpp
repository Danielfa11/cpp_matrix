#include "matrix/matrix.hpp"
#include "matrix/matrixOperations.hpp"
#include <iostream>
#include <functional>
#include <cmath>

using namespace MatrixOperations;

int main() {
    Matrix<double> mat({1.0, 2.0, 3.0, 4.0}, 2, 2);

    // isSquareMatrix
    std::cout << "isSquare: " << isSquareMatrix(mat) << "\n";  // should be 1

    // getTrace
    std::cout << "Trace: " << getTrace(mat) << "\n";           // should be 5.0

    // getTranspose
    Matrix<double> trans = getTranspose(mat);
    std::cout << "Transpose:\n";
    trans.print();                                             // [[1,3],[2,4]]

    // isSymmetric
    Matrix<double> sym({1.0, 2.0, 2.0, 1.0}, 2, 2);
    std::cout << "isSymmetric: " << isSymmetric(sym) << "\n";  // should be 1

    // getSubMatrix
    Matrix<double> mat3x3({
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    }, 3, 3);
    Matrix<double> sub = getSubMatrix(mat3x3, 0, 2, 1, 3);     // [[2,3],[5,6]]
    std::cout << "Submatrix:\n";
    sub.print();

    // apply (e.g. sigmoid)
    auto sigmoid = [](double x) {
        return 1.0 / (1.0 + std::exp(-x));
    };
    Matrix<double> activated = apply(mat3x3, sigmoid);
    std::cout << "Sigmoid applied:\n";
    activated.print();

    return 0;
}

