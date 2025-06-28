#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>


struct Shape {
    int rows;
    int cols;
    bool operator==(const Shape& other) const {
        return rows == other.rows && cols == other.cols;
    }

      std::string shape_to_string() const {
        return std::to_string(rows) + "x" + std::to_string(cols);
    }
};

template <typename T>
class Matrix {
    private:
    std::vector<std::vector<T>> matrix_;
    Shape shape_;


    public:
    Matrix(int const &rows, int const &cols): shape_{rows, cols}{
        matrix_.resize(rows, std::vector<T>(cols));
    };
    
    Matrix(std::vector<T> const &vec, int const &rows, int const &cols):shape_{rows, cols}{
        if (rows * cols  != vec.size()) {
            throw std::runtime_error("vector must have same size as col * rows");
        }
        matrix_.resize(rows, std::vector<T>(cols));
        for(int i = 0; i< rows; i++){
            for(int ii = 0; ii < cols; ii++){
                matrix_[i][ii] = vec[i * cols + ii];
            }
        }
    };

    Shape getShape() const{
        return shape_; 
    }

    void print() const{
        for(int i =0; i< shape_.rows;i++){
            for(int ii = 0;ii< shape_.cols;ii++){
                std::cout << matrix_[i][ii] << " ";
            }
            std::cout << "\n";
        }
    }
    
    void checkBounds(int row, int col) const {
        if (row < 0 || row >= shape_.rows || col < 0 || col >= shape_.cols) {
            throw std::out_of_range("Index out of bounds: (" + std::to_string(row) + ", " + std::to_string(col) + ")");
        }
    }

    void checkShapeMatch(const Matrix<T>& rhs) const {
        if (!(shape_ == rhs.shape_)) {
            throw std::runtime_error("Shape mismatch: lhs is " + shape_.shape_to_string() + ", rhs is " + rhs.getShape().shape_to_string());
        }
    }

    T& at(int row, int col) {
        checkBounds(row,col);
        return matrix_.at(row).at(col);
    }

    const T& at(int row, int col) const {
        checkBounds(row,col);
        return matrix_.at(row).at(col);
    }

    void broadcastAddRows(const Matrix<T>& bias_row) {
        
        auto bias_pair = bias_row.getShape();
        if (bias_pair.first != 1 || bias_pair.second != shape_.cols)
            throw std::runtime_error("Bias row must be shape 1×cols of matrix");

        for (int i = 0; i < shape_.rows; ++i) {
            for (int ii = 0; ii < shape_.cols; ++ii) {
                this->at(i,ii) += bias_row.at(0,ii);
            }
        }
    }

    /*
    compairs the matrixs element wise where differance bewteen 
    value must be with in 0.000001
    */
    bool isEqual(Matrix<T> const rhs) const{
        auto shape = rhs.getShape();
        if (shape.rows != shape_.rows || shape.cols != shape_.cols) return false;

        const float EPSOLON_ = 0.000001;
        for (int i = 0;i < shape.rows; i++ ){
            for(int ii = 0; ii < shape.cols; ii++){
                if (std::fabs(this->at(i,ii) - rhs.at(i,ii)) >= EPSOLON_) return false;
            }
        }
        return true;
    }
    bool operator==(const Matrix<T> &rhs) const {
        return this->isEqual(rhs);
    }
};
    // Artithmetic 
    // Matrix<T> add(Matrix<T> const &rhs) const{
    //     checkShapeMatch(rhs);
    //     Matrix<T> result(shape_.rows,shape_.cols);
    //     for(int i = 0; i < shape_.rows; i++){
    //         for(int ii = 0; ii < shape_.cols; ii++){
    //             result.at(i,ii) = this->at(i,ii) + rhs.at(i,ii);
    //         }
    //     }
    //     return result;
    // }

    // Matrix<T> subtract(Matrix<T> const &rhs) const{
    //     checkShapeMatch(rhs);
    //     Matrix<T> result(shape_.rows,shape_.cols);
    //     for(int i = 0; i < shape_.rows; i++){
    //         for(int ii = 0; ii < shape_.cols; ii++){
    //             result.at(i,ii) =this->at(i,ii) - rhs.at(i,ii);
    //         }
    //     }
    //     return result;
    // }
    /*
    // apply scalar multiplication matrix * value
    // see: https://en.wikipedia.org/wiki/Scalar_multiplication
    // */
    // Matrix<T> scalarMultiply(const T &rhs) const{
    //     Matrix<T> result(shape_.rows,shape_.cols);
    //     for(int i = 0; i < shape_.rows; i++){
    //         for(int ii = 0; ii < shape_.cols; ii++){
    //             result.at(i,ii) = this->at(i,ii) * rhs;
    //         }
    //     }
    //     return result;
    // }
    /*
    applies dot product matrix matrix multiplication
    see:https://en.wikipedia.org/wiki/Dot_product
    */
    // Matrix<T> DotProduct(Matrix<T> const  &rhs) const{
    //     auto rhs_pair = rhs.getShape();
    //     if (rhs_pair.rows != shape_.cols){
    //         throw std::runtime_error("Must have the same row and column length");
    //     }

    //     Matrix<T> result(shape_.rows,rhs_pair.cols);
    //    for(int m1_row = 0; m1_row < shape_.rows;m1_row++){
    //     for(int m2_col = 0; m2_col < rhs_pair.cols; m2_col++){
    //         T sum = 0;
    //         for(int m1_col = 0; m1_col< shape_.cols; m1_col++){
    //             sum += this->at(m1_row,m1_col) * rhs.at(m1_col,m2_col);
    //         }
    //         result.at(m1_row,m2_col) = sum;
    //     }
    // }
    // return result;
    // };

    // arithmetic overloads operators

    // Matrix<T> operator+(const Matrix<T> &rhs) const{
    //     return this->add(rhs);
    // }
    
    // Matrix<T> operator-(const Matrix<T> &rhs) const{
    //     return this->subtract(rhs);
    // }
    
    // Matrix<T> operator*(const Matrix<T> &rhs) const{
    //     return this->DotProduct(rhs);
    // }

    // template<typename Scalar>
    // Matrix<T> operator*(const Scalar &rhs) const{
    //     return this->scalarMultiply(rhs);
    // }


