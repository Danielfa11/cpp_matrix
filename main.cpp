#include "src/NueralNet/FF_NNet.hpp"
#include "src/readFile/readTxtFile.hpp"
// #include "matrix/matrix.hpp"
// #include "matrix/matrixOperations.hpp"

#include <iostream>
#include <functional>
#include <cmath>


#include <iostream>
#include <vector>

using namespace MatrixOperations;

int main() { 

    readTxtFile readFile("MNIST_txt/MNIST_test.txt");
    readFile.read(',');
    readFile.read(',');
    // std::cout << charText.size() << std::endl;
    // std::string line;
    // std::ifstream ifs("MNIST_txt/MNIST_train.txt");

    // std::vector<double> inputs;
    // std::vector<double> targets;
    // std::vector<double> predict;
    // int count = 0;
    // if (ifs.is_open()){
    //    while( getline (ifs, line)){
    //     if (count == 50){
    //         break;
    //     }
    //     count++;
        
    //     int classificaion = line.at(0);
    //     for(int i =0; i < 9; i++){
    //         if(classificaion - '0' == i){
    //             targets.push_back(1);
    //         }else{
    //             targets.push_back(0);
    //         }
    //     }
    //     line.erase(0,2);

    //     std::stringstream ss(line);
    //     std::string token;
    //     while (getline(ss, token, ',')) {
    //         inputs.push_back(std::stod(token));
    //         if(count == 2){
    //             predict.push_back(std::stod(token));
    //         }
    //         }
    //     }
    //     std::cout << count << std::endl;
    //     ifs.close();
    // };

    // std::cout << targets.size() << std::endl;
    // Matrix<double> M_i(inputs,count,784);
    // Matrix<double>T_i (targets,count,9);
    // FF_NNet MNIST_num({784,1000,1000,9});

    // Matrix<double> m_i2 = M_i / 255.0;
    // for(int i = 0; i <10; i++){
    //     Matrix<double> error =MNIST_num.train(m_i2,T_i);
    //     // if (i % 3 == 0){
    //         Shape error_shape = error.getShape();
    //         double errorSum = 0;
    //         for(int ii = 0; ii < error_shape.rows; ii++){
    //             for(int iii = 0; iii< error_shape.cols;iii++ ){
    //                 errorSum += error.at(ii,iii);
    //             }
                
    //         }
    //         std::cout << "\nTotal error for round: "<< i<<"\n"<< errorSum << std::endl;
    // }

    // MNIST_num.predict((Matrix<double>(
    //     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,84,185,159,151,60,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,222,254,254,254,254,241,198,198,198,198,198,198,198,198,170,52,0,0,0,0,0,0,0,0,0,0,0,0,67,114,72,114,163,227,254,225,254,254,254,250,229,254,254,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,66,14,67,67,67,59,21,236,254,106,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,83,253,209,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,233,255,83,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,129,254,238,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59,249,254,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,254,187,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,205,248,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,126,254,182,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,75,251,240,57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,221,254,166,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,203,254,219,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,38,254,254,77,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,224,254,115,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,254,254,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,242,254,254,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,254,254,219,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,254,207,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    //     ,1,784) /255 )).print();

    return 0;
}
