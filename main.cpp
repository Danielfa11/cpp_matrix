#include "matrix/matrix.hpp"

int main(){
Matrix<double> input({0.4, 0.3, 0.9}, 1, 3);

Matrix<double> weights1({0.2, 0.8,
                         0.4, 0.5,
                         0.1, 0.6}, 3, 2);
Matrix<double> bias1({0.1, 0.2}, 1, 2);

Matrix<double> weights2({0.3,
                         0.7}, 2, 1);
Matrix<double> bias2({0.1}, 1, 1);

// Forward pass
Matrix<double> z1 = input * weights1 + bias1;
Matrix<double> a1 = z1.apply([](double x) { return 1.0 / (1.0 + std::exp(-x)); });

Matrix<double> z2 = a1 * weights2 + bias2;
Matrix<double> output = z2.apply([](double x) { return 1.0 / (1.0 + std::exp(-x)); });

std::cout << "Predicted probability: " << output.at(0,0) << "\n";
std::cout << "Predicted class: " << ((output.at(0,0) > 0.5) ? "1" : "0") << "\n";
    return 0;
}