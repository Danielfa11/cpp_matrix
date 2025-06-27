#pragma once
#include "matrix.hpp"


namespace MatrixOperations {
    template <typename T>
    bool isSquareMatrix(Matrix<T> const &matrix)  {
        auto shape = matrix.getShape();
        return shape.rows == shape.cols;
    };

    /*
    get the trace of a square matrix tr(A)
    see: https://en.wikipedia.org/wiki/Trace_(linear_algebra)
    */
   template <typename T>
    T getTrace(Matrix<T> &matrix) {
    Shape shape = matrix.getShape(); 
    if(!isSquareMatrix(matrix)){
        throw std::runtime_error("Matrix row and cols must be of same size");
    }
    T sum = 0;
    for(int i = 0; i < shape.rows;i++){
        sum+= matrix.at(i,i);
    }
    return sum;
    };

    
     /*
    Transpose the matrixs 
    see: https://en.wikipedia.org/wiki/Transpose
    */
    template <typename T>
    Matrix<T> getTranspose(Matrix<T> const &matrix) {
        Shape shape = matrix.getShape();
        Matrix<T> result(shape.cols, shape.rows);
        for (int i = 0; i < shape.rows; ++i) {
            for (int j = 0; j < shape.cols; ++j) {
                result.at(j, i) = matrix.at(i, j);
            }
        }
        return result;
    };

      /*
    compairs the matrixs to its transpoed matrix 
    the equal comparison is true is all elements are within 0.000001 of each other 
    see: https://en.wikipedia.org/wiki/Symmetric_matrix
    */
   template <typename T>
    bool isSymmetric(Matrix<T> const &matrix) {
        return matrix == getTranspose(matrix);
    };

    /*
    rowStart: 0 indexed 
    rowEnd: exclusive end i.e last idx+1  
    colStart: 0 indexed
    colEnd: exclusive end i.e last idx+1

    return type: Matrix<T>
    */
    template <typename T>
    Matrix<T> getSubMatrix(Matrix<T> const &matrix,int rowStart, int rowEnd, int colStart, int colEnd){
        Shape shape = matrix.getShape();
        if(rowStart < 0 || rowEnd > shape.rows || colStart < 0 || colEnd > shape.cols ||  rowStart >= rowEnd || colStart >= colEnd){
            throw std::out_of_range("Matrix index out of bounds in subMatrix");
        }
        Matrix<T> result(rowEnd-rowStart, colEnd - colStart);

        for(int i = rowStart; i < rowEnd; i++){
            for(int ii = colStart; ii< colEnd; ii++){
                result.at(i-rowStart,ii-colStart) = matrix.at(i,ii);
            }
        }
        return result;
    };
        template <typename T, typename UnaryFunction>
        Matrix<T> apply(Matrix<T> matrix,UnaryFunction func) {
        auto shape = matrix.getShape();
        Matrix<T> result(shape.rows, shape.cols);
        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.cols; j++) {
                result.at(i,j) = func(matrix.at(i,j));
            }
        }
        return result;
    };

    template<typename T>
    Matrix<T> hadamardProduct(const Matrix<T> &lhs,const Matrix<T> &rhs) {
        lhs.checkShapeMatch(rhs);
        Shape shape =lhs.getShape();
        Matrix<T> result(shape.rows,shape.cols);
        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                result.at(i,ii) = lhs.at(i,ii) * rhs.at(i,ii);
            }
        }
    }
};   