#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <random>


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
    std::vector<T> matrix_;
    Shape shape_;


    public:
    Matrix(int const &rows, int const &cols): shape_{rows, cols}{};
    
    Matrix(std::vector<T> const &vec, int const &rows, int const &cols):shape_{rows, cols}{
        if (rows * cols  != vec.size()) {
            throw std::runtime_error("vector must have same size as col * rows constructor");
        }
        matrix_ = vec;
    };

    Shape getShape() const{
        return shape_; 
    }

    void print() const{
        for(int i =0; i< shape_.rows;i++){
            for(int ii = 0;ii< shape_.cols;ii++){
                std::cout << matrix_[i * shape_.cols + ii] << " ";
            }
            std::cout << "\n";
        }
    }
    
    void checkBounds(int row, int col) const {
        if (row < 0 || row >= shape_.rows || col < 0 || col >= shape_.cols) {
            throw std::out_of_range("Index out of bounds: (" + std::to_string(row) + ", " + std::to_string(col) + ")");
        }
    }

    void checkShapeMatch(const Matrix<T>& rhs, std::string operation) const {
        if (!(shape_ == rhs.shape_)) {
            throw std::runtime_error("Shape mismatch: lhs is " + shape_.shape_to_string() + ", rhs is " + rhs.getShape().shape_to_string()+ "for operation -"+operation);
        }
    }

    T& at(int row, int col) {
        checkBounds(row,col);
        return matrix_[row * shape_.cols + col];
    }

    const T& at(int row, int col) const {
        checkBounds(row,col);
         return matrix_[row * shape_.cols + col];
    }

    void broadcastAddRows(const Matrix<T>& bias_row) {
        auto bias_pair = bias_row.getShape();
        if (bias_pair.first != 1 || bias_pair.second != shape_.cols)
            throw std::runtime_error("Bias row must be shape 1 × cols of matrix");

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
    };
    bool operator==(const Matrix<T> &rhs) const {
        return this->isEqual(rhs);
    };

    // Artithmetic 
    void add(Matrix<T> const &rhs){
        checkShapeMatch(rhs, "add in place");  
        for(int i = 0; i < shape_.rows; i++){
            for(int ii = 0; ii < shape_.cols; ii++){
                this->at(i,ii) += rhs.at(i,ii);
            }
        }
    };
     void operator+=(Matrix<T> const &rhs) {
        this->add(rhs);
    };

    void subtract(Matrix<T> const &rhs) {
        checkShapeMatch(rhs, "subtract in place");
        Matrix<T> result(shape_.rows,shape_.cols);
        for(int i = 0; i < shape_.rows; i++){
            for(int ii = 0; ii < shape_.cols; ii++){
                this->at(i,ii) -= rhs.at(i,ii);
            }
        }  
    };
    void operator-=(Matrix<T> const &rhs) {
        this->subtract(rhs);
    };

    // apply scalar multiplication matrix * value
    // see: https://en.wikipedia.org/wiki/Scalar_multiplication
    // */
    template<typename Scalar>
    void scalarMultiply(Scalar const &rhs) {
        Matrix<T> result(shape_.rows,shape_.cols);
        for(int i = 0; i < shape_.rows; i++){
            for(int ii = 0; ii < shape_.cols; ii++){
                 this->at(i,ii) *= rhs;
            }
        }
    };
    template<typename Scalar>
    void operator*=(Scalar const &rhs) {
        this->scalarMultiply(rhs);
    };


};
