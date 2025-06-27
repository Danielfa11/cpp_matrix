#include "matrix/matrix.hpp"

int main(){
    std::vector<double> test = {1,2,3,2,4,5,3,5,6};
    std::vector<double> test2 ={1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.1,11.2,12.3};
    Matrix<double> first(test,3,3);
    first.print();
    std::cout << "\n";
    Matrix<double> second(test2,4,3);
    first.print();
    std::cout << "this is symetric: " <<first.isSymmetric() << "\n";
    std::cout << "this is not symetric: " <<second.isSymmetric() << "\n";
    

    return 0;
}