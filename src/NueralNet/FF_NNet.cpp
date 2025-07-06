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
        for(size_t i = 0; i < weight.size(); i++){
            weights.push_back(weight.at(i));
            biases.push_back(bias.at(i));
        }
     }


    FF_NNet::FF_NNet(const std::vector<int> &layers){
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(-1, 1);

        for(size_t i = 1; i <layers.size();i++){
            std::vector<double> weight;
            std::vector<double> bias;
            //                  input       output
            for(size_t ii = 0; ii < layers[i-1]*layers[i]; ii++){ 
                weight.push_back(dist(e2));
            }
            //                  
            for(size_t ii = 0; ii < layers[i];ii++){
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

        for(size_t i = 0; i< weights.size();i++){
            Matrix<double> z = broadcastAddRows(activations[i] * weights[i],biases[i]);
            z_values.push_back(z);
            activations.push_back(apply(z,sigmoid));    
        }

        return activations[activations.size()-1];
    };

    void FF_NNet::print(){
        std::cout << "nn weight and bias" << std::endl;
        for(size_t i =0; i < weights.size();i++){
            std::cout << "wieghts_"<<i<<" \n";
            weights[i].print();
            std::cout << "\n";
        };

        for(size_t i = 0; i <biases.size();i++){
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
        for(size_t i = 0; i< weights.size();i++){
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
        for (size_t i = weights.size() - 2; i >= 0; --i) {
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
    /*
    The file will be save in the formate with new line being a seperator
    
    layers
    W\t ...
    B\t ...
    */
    void FF_NNet::saveToFile(){
       std::string filesName = "saved_Models/ff_net.txt";
       std::ofstream ofs(filesName);
       if(!ofs){
        throw std::runtime_error("Failed to open file: " + filesName);
       };

       int layerCount = this->weights.size();

        ofs << weights[0].getShape().rows << ",";
        for(size_t i = 0; i< layerCount; i++){
            ofs << weights[i].getShape().cols;
            if(i+1 < layerCount){
                 ofs << ",";
            }
        }
        ofs << "\n";

        for(size_t i=0;i< layerCount;i++){
            const Matrix<double>& currW = weights[i];
            const Matrix<double>& currB = biases[i];

            const std::vector<double>& flatW = currW.getFlat();
            const std::vector<double>& flatB = currB.getFlat();

            ofs << "W,";
            for (size_t ii = 0; ii < flatW.size(); ii++){
                ofs << std::setprecision(8) << flatW[ii];
                if(ii + 1 < flatW.size()) {
                    ofs << ",";
                }
            }
            ofs << "\n";

            ofs << "B,";
            for(size_t ii = 0; ii < flatB.size(); ii++){
                ofs << std::setprecision(8) <<  flatB[ii];
                if(ii + 1 < flatB.size()) {
                    ofs << ",";
                }
            };
            ofs << "\n";
                
        };
        ofs.close();
    }
    void FF_NNet::backwardPass(){};

    
    std::vector<int> parseLayers(const std::string &line, char delim) {
        std::vector<int> layers;
        size_t start = 0;
        while(start < line.size()){
            size_t end = line.find(delim,start);
            if(end == std::string::npos) {
                end = line.size();
            };
            std::string layer = line.substr(start,end-start);
            layers.push_back(std::stoi(layer));
            start = end + 1;
        };
        return layers;
    }

    std::vector<double> parseDoubles(const std::string &line, char delim){
        size_t start = 0;
        size_t end;
        std::vector<double> result;
        while(start < line.size()){
            end = line.find(delim,start);
            if(end == std::string::npos) {
                end = line.size();
            }
            result.push_back(std::stod(line.substr(start,end-start)));
            start = end + 1;
        }
        return result;
    }

    FF_NNet readFromFile(std::string path){
        std::ifstream ifs(path);
        if (!ifs) {
            throw std::runtime_error("Failed to open file: " + path);
        };
        const char delim = ',';
        const char weightChar = 'W';
        const char biasChar = 'B';

        std::vector<int> layers;
        std::vector<Matrix<double>> weights;
        std::vector<Matrix<double>> biases;
        
        std::string line;
        std::getline(ifs,line);
        layers = parseLayers(line,delim);
        
        for(size_t i =1; i < layers.size(); i++){

            int rows = layers[i-1];
            int cols = layers[i];

            // reads the weights in for a row
            if (!std::getline(ifs, line) || line.empty() || line[0] != weightChar){
                throw std::runtime_error("Expected weight line starting with 'W'");
            }
            // ignore the the clasification for row type of W\t
            std::vector<double> weightVal = parseDoubles(line.substr(2),delim); 
            if(weightVal.size() != static_cast<size_t>(rows * cols)){
                throw std::runtime_error("Weight matrix has incorrect size");
            }
            weights.emplace_back(Matrix<double>(weightVal,rows,cols));
            
            // read in the bias for the matrix
            if(!std::getline(ifs,line) || line.empty() || line[0] != biasChar){
                throw std::runtime_error("Expected weight line starting with 'B'");
            }
            // substr is for the file format to ignor the B\t
            std::vector<double> biasValue = parseDoubles(line.substr(2),delim);
            if(biasValue.size() != static_cast<size_t>(cols)){
                throw std::runtime_error("Bias matrix has incorrect size");
            }
            biases.emplace_back(Matrix<double>(biasValue,1,cols));
        }
        ifs.close();
        return FF_NNet(layers,biases,weights);
    };
