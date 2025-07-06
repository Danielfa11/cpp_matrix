#ifndef MODELS_SRC_NUERALNET_FF_NNENT_H
#define MODELS_SRC_NUERALNET_FF_NNENT_H

#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <stddef.h>

#include "../matrix/matrix.hpp"
#include "../matrix/matrixOperations.hpp"

class FF_NNet{
    using Func = std::function<Matrix<double>(const Matrix<double>&)>;
    
    std::vector<Matrix<double>> weights;
    std::vector<Matrix<double>> biases;
    // Func activation;
    // Func activation_derivative;   // error delta at each layer (used during backprop)
    
    public:
    FF_NNet(const std::vector<int> &layers);
    // to be able to manually set the ever paramater
    FF_NNet(const std::vector<int> &layers,
                      const std::vector<Matrix<double>> bias,
                      const std::vector<Matrix<double>> weights);


    Matrix<double> train(const Matrix<double> &input,const Matrix<double> &target);

    Matrix<double> predict(const Matrix<double> &inputs);

    void print();
    
    void saveToFile();

    private:
    Matrix<double> fowardPass(const Matrix<double> &input, const Matrix<double> &target);

    void backwardPass();

};

FF_NNet readFromFile(std::string path);

#endif // MODELS_SRC_NUERALNET_FF_NNENT_H
