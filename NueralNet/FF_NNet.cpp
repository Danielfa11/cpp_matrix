#include "FF_NNet.hpp"

using namespace MatrixOperations;
double sigmoid(const double &x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_prime(const double &x){
    const double sigmoid_x = sigmoid(x);
    return sigmoid_x * (1-sigmoid_x);
}

double MSE(const double &x){
    return 0.5 * (x * x);
};
     FF_NNet::FF_NNet(const std::vector<int> &layers,
                      const std::vector<Matrix<double>> bias,
                      const std::vector<Matrix<double>> weight){
        for(int i = 0; i < weight.size(); i++){
            weights.push_back(weight.at(i));
            biases.push_back(bias.at(i));
        }
     }


    FF_NNet::FF_NNet(const std::vector<int> &layers){
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(-1, 1);

        for(int i = 1; i <layers.size();i++){
            int input_size = layers[i];
            int output_size = layers[i - 1];

            std::vector<double> weight;
            std::vector<double> bias;
            for(int ii = 0; ii < input_size*output_size; ii++){ 
                weight.push_back(dist(e2));
            }
            for(int ii = 0; ii < input_size;ii++){
                bias.push_back(dist(e2));
            }
            weights.push_back(Matrix<double>(weight, output_size, input_size));
            biases.push_back(Matrix<double>(bias, 1, input_size));
        }
    };

    void FF_NNet::train(const Matrix<double> &input,const Matrix<double> &target){
        fowardPass(input,target);
    };

    void FF_NNet::predict(const Matrix<double> &input){};

    void FF_NNet::print(){
        for(int i =0; i < weights.size();i++){
            std::cout << "wieghts"<<i<<" \n";
            weights[i].print();
            std::cout << "\n";
        };

        for(int i = 0; i <biases.size();i++){
            std::cout << "bias"<<i<<" \n";
            biases[i].print();
            std::cout << "\n";
        }

    };
    
    void FF_NNet::fowardPass(const Matrix<double> &inputs, const Matrix<double> &target){
        // foward Pass
        std::vector<Matrix<double>> activations;
        std::vector<Matrix<double>> z_values;
        activations.push_back(inputs);

        for(int i = 0; i< weights.size();i++){
            Matrix<double> z = broadcastAddRows(weights[i] * activations[i],biases[i]);
            z_values.push_back(z);
            activations.push_back(apply(z,sigmoid));    
        }
       // -----------------------------------------------------
       // backwardPass
        std::vector<Matrix<double>> deltas;

        Matrix<double> output = activations[activations.size()-1];
        Matrix<double> error = output - target;
        
        // get first gradiant
        Matrix<double> delta_output  = hadamardProduct(error,
            apply(z_values.back(),sigmoid_prime)
        );
        deltas.push_back(delta_output);

        // starting from end, so skips the last node, when starting
        for (int i = weights.size() - 2; i >= 0; --i) {
            // weight^T * last delta, for each row
            Matrix<double> delta_prev = hadamardProduct(
                 ~weights[i + 1] * deltas.back(),
                apply(z_values[i], sigmoid_prime)
            );
            deltas.push_back(delta_prev); 
        }
        std::reverse(deltas.begin(), deltas.end());

        //TODO move this to be a parameter
        // or most fancy stuff.
        double learnRate = 0.1;

        for (size_t i = 0; i < weights.size(); ++i) {
            Matrix<double> a_prev = activations[i];
            Matrix<double> delta = deltas[i];
            // calculate gradiant for weights 
            std::cout << "delta"<<i << std::endl;
            delta.print();
            std::cout << std::endl;
            Matrix<double> grad_w = delta * ~a_prev ;
        
            Matrix<double> grad_b = rowWiseSum(delta);

            // Update the weights and biases
            std::cout << "gradw"<<i << std::endl;
            grad_w.print();
            std::cout << std::endl;
            weights[i] = weights[i] - grad_w * learnRate;
            biases[i] = biases[i] - grad_b * learnRate;
        }
        //TODO think placing some type of output down here???        
    };

    void FF_NNet::backwardPass(){};
