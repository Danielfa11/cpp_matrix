#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "../src/matrix/matrix.hpp"
#include "../src/matrix/matrixOperations.hpp"

using namespace MatrixOperations;

TEST_CASE("Matrix creation and shape", "[Matrix]") {
    Matrix<double> mat(2, 3);
    auto shape = mat.getShape();
    CHECK(shape.rows == 2);
    CHECK(shape.cols == 3);

    std::vector<double> vec = {1, 2, 3, 4, 5, 6};
    Matrix<double> mat2(vec, 2, 3);
    CHECK(mat2.at(1, 2) == 6.0);
};



TEST_CASE("Matrix addition in place","[Matrix]"){
    Matrix<int> mat1({1,2,3,4,5,6},2,3);
    Matrix<int> mat2({1,2,3,4,5,6},2,3);
    Matrix<int> expected({2,4,6,8,10,12},2,3);
    mat1+=mat2;
    CHECK(mat1 == expected);
    Matrix<int> throws(4,4);
    CHECK_THROWS_AS(mat1+=throws, std::runtime_error);
};
TEST_CASE("Matrix subtaction in place","[Matrix]"){
    Matrix<int> mat1({2,4,6,8,10,12},2,3);
    Matrix<int> mat2({1,2,3,4,5,6},2,3);
    Matrix<int> expected({1,2,3,4,5,6},2,3);
    
    mat1-=mat2;
    CHECK(mat1 == expected);
    Matrix<int> throws(4,4);
    CHECK_THROWS_AS(mat1-=throws, std::runtime_error);
};

TEST_CASE("Matrix scalar in place","[Matrix]"){
    Matrix<int> mat1({1,2,3,4,5,6},2,3);
    int scalar = 3;
    Matrix<int> expected({3,6,9,12,15,18},2,3);
    
    mat1*=scalar;
    CHECK(mat1 == expected);
    Matrix<int> throws(4,4);
    CHECK_THROWS_AS(mat1-=throws, std::runtime_error);
};

// THIS ABILITY IS ON HOLD until futher thought
// TEST_CASE("Matrix dotProduct in place", "[MatrixOps]") {
//     Matrix<double> a({1, 2, 3, 4}, 2, 2);
//     Matrix<double> b({5, 6, 7, 8}, 2, 2);
//     Matrix<double> expected({19, 22, 43, 50}, 2, 2);
//     a.print();
//     a*=b;

//     a.print();
//     CHECK(a == expected);

//     Matrix<double> bad({1, 2, 3, 4, 5, 6}, 3, 2);
//     CHECK_THROWS_AS(dotProduct(a, bad), std::runtime_error);
// }


TEST_CASE("isSquareMatrix", "[MatrixOps]") {
    Matrix<double> square({1, 2, 3, 4}, 2, 2);
    Matrix<double> nonSquare({1, 2, 3, 4, 5, 6}, 2, 3);

    CHECK(isSquareMatrix(square));
    CHECK_FALSE(isSquareMatrix(nonSquare));
};


TEST_CASE("getTrace", "[MatrixOps]") {
    Matrix<double> square({1, 2, 3, 4}, 2, 2);
    CHECK(getTrace(square) == Catch::Approx(5.0));

    Matrix<double> nonSquare({1, 2, 3, 4, 5, 6}, 2, 3);
    CHECK_THROWS_AS(getTrace(nonSquare), std::runtime_error);
};

TEST_CASE("getTranspose", "[MatrixOps]") {
    Matrix<double> mat({1, 2, 3, 4, 5, 6}, 2, 3);
    Matrix<double> expected({1, 4, 2, 5, 3, 6}, 3, 2);
    CHECK(getTranspose(mat) == expected);
}

TEST_CASE("isSymmetric", "[MatrixOps]") {
    Matrix<double> sym({1, 2, 2, 1}, 2, 2);
    Matrix<double> nonSym({1, 0, 3, 4}, 2, 2);
    CHECK(isSymmetric(sym));
    CHECK_FALSE(isSymmetric(nonSym));
};

TEST_CASE("getSubMatrix", "[MatrixOps]") {
    Matrix<double> mat({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    Matrix<double> expected({2, 3, 5, 6}, 2, 2);
    auto sub = getSubMatrix(mat, 0, 2, 1, 3);
    CHECK(sub == expected);

    CHECK_THROWS_AS(getSubMatrix(mat, -1, 2, 0, 2), std::out_of_range);
};

TEST_CASE("apply function to matrix", "[MatrixOps]") {
    Matrix<double> mat({1, 2, 3, 4}, 2, 2);
    Matrix<double> expected({1, 4, 9, 16}, 2, 2);
    auto result = apply(mat, [](double x) { return x * x; });
    CHECK(result == expected);
};

TEST_CASE("hadamardProduct", "[MatrixOps]") {
    Matrix<double> a({1, 2, 3, 4}, 2, 2);
    Matrix<double> b({5, 6, 7, 8}, 2, 2);
    Matrix<double> expected({5, 12, 21, 32}, 2, 2);
    CHECK(hadamardProduct(a, b) == expected);

    Matrix<double> bad({1, 2, 3}, 3, 1);
    CHECK_THROWS_AS(hadamardProduct(a, bad), std::runtime_error);
};

TEST_CASE("add and subtract", "[MatrixOps]") {
    Matrix<double> a({1, 2, 3, 4}, 2, 2);
    Matrix<double> b({4, 3, 2, 1}, 2, 2);

    Matrix<double> expectedSum({5, 5, 5, 5}, 2, 2);
    Matrix<double> expectedDiff({-3, -1, 1, 3}, 2, 2);

    CHECK(add(a, b) == expectedSum);
    CHECK(subtract(a, b) == expectedDiff);
};

TEST_CASE("scalarMultiply", "[MatrixOps]") {
    Matrix<double> a({1, 2, 3, 4}, 2, 2);
    Matrix<double> expected({2, 4, 6, 8}, 2, 2);

    CHECK(scalarMultiply(a, 2.0) == expected);
    CHECK((a * 2.0) == expected);
    CHECK((2.0 * a) == expected);
}

TEST_CASE("dotProduct", "[MatrixOps]") {
    Matrix<double> a({1, 2, 3, 4}, 2, 2);
    Matrix<double> b({5, 6, 7, 8}, 2, 2);
    Matrix<double> expected({19, 22, 43, 50}, 2, 2);

    
    CHECK(dotProduct(a, b) == expected);
    CHECK((a * b) == expected);

    Matrix<double> c({1,2,3,4,5,6},3,2);
    Matrix<double> d({1,2,3,4},2,2);
    Matrix<double>expected2({7,10,15,22,23,34},3,2);
    CHECK(dotProduct(c,d) == expected2);
    
    Matrix<double> bad({1, 2, 3, 4, 5, 6}, 3, 2);
    CHECK_THROWS_AS(dotProduct(a, bad), std::runtime_error);
}

