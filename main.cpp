#include "matrix/matrix.hpp"
#include "matrix/matrixOperations.hpp"
#include <iostream>
#include <functional>
#include <cmath>

using namespace MatrixOperations;

double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}


int main() {
       
   Matrix<double> input({0.4, 0.3, 0.9}, 1, 3);

    Matrix<double> weights1({0.2, 0.8,
                            0.4, 0.5,
                            0.1, 0.6}, 3, 2);
    Matrix<double> bias1({0.1, 0.2}, 1, 2);

    Matrix<double> weights2({0.3,
                            0.7}, 2, 1);
    Matrix<double> bias2({0.1}, 1, 1);

    // Forward pass
    Matrix<double> z1 = (input * weights1) + bias1;
    Matrix<double> a1 = apply(z1,sigmoid);

    Matrix<double> z2 = a1 * weights2 + bias2;
    Matrix<double> output = apply(z2,sigmoid);


    // backward pass
    // double y = 1.0;  // your target

    // // Grab the scalar output value
    // double y_hat = output.at(0, 0);  

    // // Compute dz2 = y_hat - y
    // Matrix<double> dz2({y_hat - y}, 1, 1);
    
    // === STEP 2: Compute dw2 and db2 ===
    // Matrix<double> a1_T = getTranspose(a1);  // shape (2×1)
    // Matrix<double> dw2 = a1_T * dz2;                           // shape (2×1)
    // Matrix<double> db2 = dz2;   
    
    // Matrix<double> da1 = dz2 * getTranspose(weights2);

    // Matrix<double> dz1 = da1 * apply(z1,sigmoid);

    // Matrix<double> dw1 = getTranspose(input) * dz1;

    // Matrix<double> db1 = dz1;

    // double learning_rate = 0.1;
    // weights1 = (weights1 - dw1) * learning_rate;
    // bias1    = (bias1 - db1) * learning_rate;
    // weights2 = (weights2 - dw2) * learning_rate;
    // bias2    = (bias2 - db2) * learning_rate;
return 0;
}

