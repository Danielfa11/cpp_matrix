#include "../matrix/matrix.hpp"
#include "../matrix/matrixOperations.hpp"
#include <functional>

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

    void train(const Matrix<double> &input,const Matrix<double> &target);

    void predict(const Matrix<double> &input);

    void print();
    

    private:
    void fowardPass(const Matrix<double> &input, const Matrix<double> &target);

    void backwardPass();

};
