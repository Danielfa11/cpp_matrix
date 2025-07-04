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
            int input_size = layers[i-1];
            int output_size = layers[i];

            std::vector<double> weight;
            std::vector<double> bias;
            //                  input       output
            for(int ii = 0; ii < layers[i-1]*layers[i]; ii++){ 
                weight.push_back(dist(e2));
            }
            //                  
            for(int ii = 0; ii < layers[i];ii++){
                bias.push_back(dist(e2));
            }
            weights.push_back(Matrix<double>(weight,layers[i-1], layers[i]));
            biases.push_back(Matrix<double>(bias,1,layers[i]));
        }
    };

    Matrix<double> FF_NNet::train(const Matrix<double> &input,const Matrix<double> &target){
        return fowardPass(input,target);
    };

    Matrix<double> FF_NNet::predict(const Matrix<double> &inputs){
        std::vector<Matrix<double>> activations;
        std::vector<Matrix<double>> z_values;
        activations.push_back(inputs);

        for(int i = 0; i< weights.size();i++){
            Matrix<double> z = broadcastAddRows(activations[i] * weights[i],biases[i]);
            z_values.push_back(z);
            activations.push_back(apply(z,sigmoid));    
        }

        return activations[activations.size()-1];
    };

    void FF_NNet::print(){
        std::cout << "nn weight and bias" << std::endl;
        for(int i =0; i < weights.size();i++){
            std::cout << "wieghts_"<<i<<" \n";
            weights[i].print();
            std::cout << "\n";
        };

        for(int i = 0; i <biases.size();i++){
            std::cout << "bias"<<i<<" \n";
            biases[i].print();
            std::cout << "\n";
        }

    };
    
    Matrix<double> FF_NNet::fowardPass(const Matrix<double> &inputs, const Matrix<double> &target){
        // foward Pass
        std::vector<Matrix<double>> activations;
        std::vector<Matrix<double>> z_values;
        activations.push_back(inputs);
        for(int i = 0; i< weights.size();i++){
            Matrix<double> z = broadcastAddRows(activations[i] * weights[i],biases[i]);
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
                deltas.back() * ~weights[i + 1],
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
            Matrix<double> grad_w =  ~a_prev * delta;
            
            Matrix<double> grad_b = colsSum(delta);
            
            // Update the weights and biases
            weights[i] = weights[i] - grad_w * learnRate;
            biases[i] = biases[i] - grad_b * learnRate;
        }    
        return error;
    };

    void FF_NNet::backwardPass(){};
