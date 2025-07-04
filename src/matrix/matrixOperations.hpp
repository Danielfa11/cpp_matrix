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
        std::vector<T> flat_mat(shape.rows * shape.cols);
        for (int i = 0; i < shape.rows; ++i) {
            for (int ii = 0; ii < shape.cols; ++ii) {
                flat_mat[ii * shape.rows + i] = matrix.at(i,ii);  
            }
        }
        return Matrix<T> (flat_mat,shape.cols,shape.rows);
    };
     template<typename T>
       Matrix<T> operator~(Matrix<T> const &rhs) {
        return getTranspose(rhs);
    }

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
        int rows =(rowEnd-rowStart);
        int cols = (colEnd - colStart);
        std::vector<T> flat_mat(rows * cols);
        
        for(int i = rowStart; i < rowEnd; i++){
            for(int ii = colStart; ii< colEnd; ii++){
                flat_mat[(i-rowStart) * cols + (ii-colStart)] = matrix.at(i,ii);
            }
        }
        return Matrix<T>(flat_mat,rows,cols);
    };

    template <typename T, typename UnaryFunction>
    Matrix<T> apply(const Matrix<T> &matrix,UnaryFunction func) {
        Shape shape = matrix.getShape();
        // Matrix<T> result(shape.rows, shape.cols);
        std::vector<T> flat_mat(shape.rows * shape.cols);
        for (int i = 0; i < shape.rows; i++) {
            for (int ii = 0; ii < shape.cols; ii++) {
                flat_mat[i * shape.cols + ii] = func(matrix.at(i,ii));
            }
        }
        return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };

    template<typename T>
    Matrix<T> hadamardProduct(const Matrix<T> &lhs,const Matrix<T> &rhs) {
        lhs.checkShapeMatch(rhs,"hadamard product");
        Shape shape =lhs.getShape();
        
        std::vector<T> flat_mat(shape.rows * shape.cols);
        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                flat_mat[i * shape.cols + ii] = lhs.at(i,ii) * rhs.at(i,ii);
            }
        }
        return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };

    template<typename T>
    Matrix<T> add(Matrix<T>const &lhs ,Matrix<T> const &rhs) {
        lhs.checkShapeMatch(rhs, "add");
        Shape shape = lhs.getShape();
        std::vector<T> flat_mat(shape.rows * shape.cols);

        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                flat_mat[i * shape.cols + ii] = lhs.at(i,ii) + rhs.at(i,ii);
            }
        }
        return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };
    template<typename T>
       Matrix<T> operator+( Matrix<T> const &lhs, Matrix<T> const &rhs) {
        return add(lhs,rhs);
    }

    template<typename T>
    Matrix<T> subtract(Matrix<T> const &lhs,Matrix<T> const &rhs) {
        lhs.checkShapeMatch(rhs,"subtract");
        Shape shape = lhs.getShape();
        std::vector<T> flat_mat(shape.rows * shape.cols);
        
        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                 flat_mat[i * shape.cols + ii] = lhs.at(i,ii) - rhs.at(i,ii);
            }
        }
        return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };
    template<typename T>
     Matrix<T> operator-( Matrix<T> const &lhs, Matrix<T> const &rhs){
        return subtract(lhs,rhs);
    }

    /*
    apply scalar multiplication matrix * value
    see: https://en.wikipedia.org/wiki/Scalar_multiplication
    */
   template<typename T, typename Scalar>
    Matrix<T> scalarMultiply(Matrix<T> const &lhs,const Scalar &rhs) {
        Shape shape = lhs.getShape();
        std::vector<T> flat_mat(shape.rows * shape.cols);

        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                flat_mat[i * shape.cols + ii] = lhs.at(i,ii) * rhs;
            }
        };
         return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };
    template<typename T,typename Scalar>
    Matrix<T> operator*(Matrix<T> const &lhs, Scalar const &rhs){
        return scalarMultiply(lhs,rhs);
    }
    template<typename T,typename Scalar>
    Matrix<T> operator*( Scalar const &lhs,Matrix<T> const &rhs){
        return scalarMultiply(rhs,lhs);
    }

    template<typename T, typename Scalar>
    Matrix<T> scalarDivide(Matrix<T> const &lhs,const Scalar &rhs) {
        Shape shape = lhs.getShape();
        std::vector<T> flat_mat(shape.rows * shape.cols);
        if (rhs == 0) {
            throw std::runtime_error("cant divide by zero");
        }
        for(int i = 0; i < shape.rows; i++){
            for(int ii = 0; ii < shape.cols; ii++){
                flat_mat[i * shape.cols + ii] = lhs.at(i,ii) / rhs;
            }
        };
         return Matrix<T>(flat_mat,shape.rows,shape.cols);
    };
    template<typename T,typename Scalar>
    Matrix<T> operator/(Matrix<T> const &lhs, Scalar const &rhs){
        return scalarDivide(lhs,rhs);
    }

        /*
    applies dot product matrix matrix multiplication
    see:https://en.wikipedia.org/wiki/Dot_product
    */
   template <typename T>
    Matrix<T> dotProduct(Matrix<T> const  &lhs,Matrix<T> const  &rhs){
        Shape lhs_shape = lhs.getShape();
        Shape rhs_shape = rhs.getShape();  
        if (lhs_shape.cols != rhs_shape.rows) {
            throw std::runtime_error("Shape mismatch: lhs is " +lhs_shape.shape_to_string() + ", rhs is " + rhs_shape.shape_to_string() + " in dot product");
        }
       std::vector<T> flat_mat(lhs_shape.rows * rhs_shape.cols);
        int count = 0;
       for(int m1_row = 0; m1_row < lhs_shape.rows;m1_row++){
        for(int m2_col = 0; m2_col < rhs_shape.cols; m2_col++){
            T sum = 0;
            for(int m1_col = 0; m1_col< lhs_shape.cols; m1_col++){
                sum += lhs.at(m1_row,m1_col) * rhs.at(m1_col,m2_col);
            }

            flat_mat[m1_row * rhs_shape.cols + m2_col] = sum;

        }
    }
    return Matrix<T>(flat_mat,lhs_shape.rows,rhs_shape.cols);
    };
    template <typename T>
    Matrix<T> operator*(const Matrix<T>  &lhs, const Matrix<T>  &rhs) {
        return dotProduct(lhs,rhs);
    }

    template <typename T>
    Matrix<T> broadcastAddRows(const Matrix<T>  &lhs, const Matrix<T>  &bias) {
        Shape lhs_shape = lhs.getShape();
        Shape bias_shape = bias.getShape(); 
        if (bias_shape.rows != 1 || bias_shape.cols != lhs_shape.cols)
            throw std::runtime_error("Bias must be shape 1 × cols, had :"+ bias_shape.shape_to_string() + " and addition with " + lhs_shape.shape_to_string());
        std::vector<T> flat_mat(lhs_shape.rows * lhs_shape.cols);
        
        /*
          1 2 3    2x4 need 1x4
          4 4 6 +
        */
        for (int i = 0; i < lhs_shape.rows; ++i) {
            for (int ii = 0; ii < lhs_shape.cols; ++ii) {
                flat_mat[i * bias_shape.cols + ii] = lhs.at(i,ii) + bias.at(0,ii);
            }
        }
        return Matrix<T>(flat_mat,lhs_shape.rows,lhs_shape.cols);
    }

    template <typename T>
    Matrix<T> colsSum(const Matrix<T>& mat) {
        Shape shape = mat.getShape();
        std::vector<T> result(shape.cols, 0);
        for(int i = 0; i<shape.cols;i++){
            for(int ii =0;ii<shape.rows;ii++){
                result[i] += mat.at(ii,i);
            }
        }
        return Matrix<T>(result, 1, shape.cols); // 1 row, N columns
    }
};   