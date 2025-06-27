#include <catch2/catch_test_macros.hpp>
#include "../matrix/matrix.hpp"
#include "../matrix/matrixOperations.hpp"

TEST_CASE( "Matrix Constructor empty Defaults of all zero", "[single-file]" ) {
    Matrix<double> m1(5,5);
                        
    bool isAllZeroInitualized = true;
    for(int i= 0; i < 5;i++){
       for(int ii = 0; ii < 5;ii++){
        if (m1.at(i,ii) != 0) 
            isAllZeroInitualized =false; 
       }
    }
    Shape m1Shape = m1.getShape();
    REQUIRE(isAllZeroInitualized);
    REQUIRE(m1Shape.rows == 5);
    REQUIRE(m1Shape.cols == 5);
}

TEST_CASE ("Matrix Constructor with passed in vector"){
    std::vector<double> v1 = {1,2,3,
                              4,5,6,
                              7,8,9};

    Matrix<double> m1(v1,3,3);
    bool isInitualizedCorrect = true;
    for(int i = 0; i < 3; i++){
        for(int ii = 0; ii<3;ii++){
            if (m1.at(i,ii) != v1[i*3 + ii]) 
                isInitualizedCorrect = false;
        }
    }
    REQUIRE(isInitualizedCorrect);

}

