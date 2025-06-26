#include "matrix/matrix.hpp"

int main(){
    std::vector<int> test = {1,2,3,4,5,6,7,8,9};
    Matrix<int> first(test,3,3);
    Matrix<int> second(test,3,3);


    Matrix<int> newO = first + second;

    newO.print();
   
    return 0;
}