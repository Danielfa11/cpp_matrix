#include "matrix/matrix.hpp"

int main(){
    std::vector<int> test = {1,2,3,4,5,6,7,8,9,10,11,12};
    Matrix<int> first(test,3,4);
    Matrix<int> second(test,4,3);

     first.print();

     first*=second;

     first.print();

    return 0;
}