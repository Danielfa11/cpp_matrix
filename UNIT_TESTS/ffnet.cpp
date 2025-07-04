#include "../matrix/matrix.hpp"
#include "../matrix/matrixOperations.hpp"
#include "../NueralNet/FF_NNet.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <cmath>
#include <vector>
#include <iostream>

using namespace MatrixOperations;
// Sigmoid activation and derivative
double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_prime(double x) {
    double s = sigmoid(x);
    return s * (1 - s);
}

// Hardcoded test based on earlier example
TEST_CASE("Forward and Backward Pass - Hardcoded Example") {
    // Input x: 2x1
    Matrix<double> x({1, 0}, 2, 1);

    // Hidden layer weights (2x2) and biases (2x1)
    Matrix<double> W1({
        1, 1,
        0.5, -0.5
    }, 2, 2);

    Matrix<double> b1({0.5, 0}, 2, 1);

    // Output layer weights (1x2) and bias (1x1)
    Matrix<double> W2({1, 1}, 1, 2);
    Matrix<double> b2({0.5}, 1, 1);

    std::vector<Matrix<double>> weights = {W1,W2};
    std::vector<Matrix<double>> biases = {b1,b2};
    // FF_NNet test = FF_NNet({2,2,1},
    //                   biases,
    //                   weights);

    // Forward pass
    Matrix<double> z1 = W1 * x + b1;
    Matrix<double> a1 = apply(z1, sigmoid);
    
    Matrix<double> z2 = W2 * a1 + b2;
    Matrix<double> a2 = apply(z2, sigmoid);

    // Target output
    Matrix<double> y({1.0}, 1, 1);

    // Output delta: (a2 - y) * sigmoid'(z2)
    Matrix<double> error = a2 - y;
    Matrix<double> dz2 = hadamardProduct(error, apply(z2, sigmoid_prime));

    // Hidden delta: (W2^T * dz2) * sigmoid'(z1)
    Matrix<double> dz1 = hadamardProduct(
        ~W2 * dz2,
        apply(z1, sigmoid_prime)
    );
    dz2.print();
    dz1.print();
    // Assertions
    REQUIRE(a2.getShape() == Shape{1,1});
    REQUIRE(std::abs(a2.at(0,0) - 0.8743) < 0.001);

    REQUIRE(std::abs(dz2.at(0,0) + 0.0138) < 0.001); // ~ -0.0138
    REQUIRE(std::abs(dz1.at(0,0) + 0.0021) < 0.001); // ~ -0.0021
    REQUIRE(std::abs(dz1.at(1,0) + 0.0032) < 0.001); // ~ -0.0032
}
