#include "NueralNet/FF_NNet.hpp"
// #include "matrix/matrix.hpp"
// #include "matrix/matrixOperations.hpp"

#include <iostream>
#include <functional>
#include <cmath>

// using namespace MatrixOperations;

int main() { 
    // w1 - 2x2 b1 - 1x2
    // w2 - 1x2 b2 - 1x1
   Matrix<double> X({1, 0}, 2, 1);

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
    FF_NNet test = FF_NNet({2,2,1},
                      biases,
                      weights);

    Matrix<double> target({1.0}, 1, 1);
    test.train(X,target);
    test.print();
    // Matrix<double> in({ 1,2,3,
    //                     4,5,6,
    //                     7,8,9,
    //                     10,11,12,
    //                     13,14,15},5,3);

    // myNet.train(in,Matrix<double>({1,
    //                                1,
    //                                0,
    //                                1,
    //                                0},5,1));
    // Matrix<double> input({0,1,1},1,3);
    // Matrix<double> weight({0.351,-0.097,0.457,
    //                        1.076,-0.165,-0.165,
    //                        1.116,0.542,-0.331},3,3);

    // Matrix<double> h1 =apply((input * weight),sigmoid);

    // Matrix<double>weight2({0.383,
    //                       -0.327,
    //                       -0.329},3,1);
    // h1.print();
    // std::cout << "\n";
    // apply((h1 * weight2),sigmoid).print();
    return 0;
}


// double sigmoid(const double &x) {
//     return 1.0 / (1.0 + std::exp(-x));
// }

// double sigmoid_prime(double &x){
//     double sig_value = sigmoid(x);
//     return  sig_value * (1 - sig_value);
// }

// double reLU(const double &x) {
//     if (x <= 0) return 0;
//     return x;
// }

// bool check(const double &x){
//     if(x > 0){
//         return 1;
//     }
//     return 0;
// }