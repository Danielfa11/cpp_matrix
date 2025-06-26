#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class Matrix {
    
    std::vector<std::vector<T>> matrix_;
    int row_len = 0;
    int col_len = 0;

    public:
    Matrix(int const &rows, int const &cols){
        matrix_.resize(rows, std::vector<T>(cols));
        row_len = rows;
        col_len = cols;
    };
    
    Matrix(std::vector<T> const &vec, int const &rows, int const &cols){
        if (rows * cols  != vec.size()) {
            throw std::runtime_error("vector must have same size as col * rows");
        }

        matrix_.resize(rows, std::vector<T>(cols));
        row_len = rows;
        col_len = cols;

        for(int i = 0; i< rows; i++){
            for(int ii = 0; ii < cols; ii++){
                matrix_[i][ii] = vec[i * cols + ii];
            }
        }
    };

    std::pair<int,int> size() const{
        return std::make_pair(row_len,col_len);
    }

    void const print(){
        for(int i =0; i< row_len;i++){
            for(int ii = 0;ii< col_len;ii++){
                std::cout << matrix_[i][ii] << " ";
            }
            std::cout << "\n";
        }
    }
    // Optional: to access or modify elements
    T& at(int row, int col) {
        if(row > row_len ){
            throw std::runtime_error("matrixs out of bounds row");
        }

        if(col > col_len){
            throw std::runtime_error("matrixs out of bounds col");
        }
        return matrix_[row][col];
    }

    const T& at(int row, int col) const {
        return matrix_.at(row).at(col);
    }

    // TODO
    void insertRow(std::vector<T> newRow){};
    // TODO
    void insertColumn(std::vector<T> newCol){};

    // TODO
    void remove(){};

    void addInPlace(Matrix<T> const &lhs){
        auto lhs_pair = lhs.size();
        if(lhs_pair.first != row_len || lhs_pair.second != col_len) {
            throw std::runtime_error("matrixs must be of same size");
        }
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix_[i][ii] += lhs.at(i,ii);
            }
        }
        
    };

    Matrix<T> add(Matrix<T> const &lhs){
        auto lhs_pair = lhs.size();
        if(lhs_pair.first != row_len || lhs_pair.second != col_len) {
            throw std::runtime_error("matrixs must be of same size");
        }

        Matrix<T> result(row_len,col_len);
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                result.at(i,ii) = this->at(i,ii) + lhs.at(i,ii);
            }
        }
        return result;
    }

    void subtractionInPlace(Matrix<T> const &lhs){
        auto lhs_pair = lhs.size();
        if(lhs_pair.first != row_len || lhs_pair.second != col_len) {
            throw std::runtime_error("matrixs must be of same size");
        }
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix_[i][ii] -= lhs.at(i,ii);
            }
        }
    };

    // todo operator
    void ScalarMultiplication(const int &lhs){
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                this->at(i,ii) *= lhs;
            }
        }
    };

    // todo operator
    void ScalarMultiplication(const double lhs){
         for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                this->at(i,ii) *= lhs;
            }
        }
    };

    // TODO
    void Transpose(){};
    
    Matrix<T> inverse(){};

    

    Matrix<T> Multiply(Matrix<T> const  &lhs){{
        auto lhs_pair = lhs.size();
        if (col_len != lhs_pair.first){
            throw std::runtime_error("Matrics being muiltiplty must have martix1.cols.len = martix2.rows.lens");
        }
        Matrix<T> result(row_len,lhs_pair.second);
       for(int m1_row = 0; m1_row < row_len;m1_row++){
        for(int m2_col = 0; m2_col < lhs_pair.second; m2_col++){
            T sum = 0;
            for(int m1_col = 0; m1_col< col_len; m1_col++){
                sum += this->at(m1_row,m1_col) * lhs.at(m1_col,m2_col);
            }
            result.at(m1_row,m2_col) = sum;
        }
    }
    return result;

    }};


    void operator+=(const Matrix<T> &lhs){
        this->addInPlace(lhs);
    }

    Matrix<T> operator+(const Matrix<T> &lhs){
        return this->add(lhs);
    }
    
    Matrix<T> operator*(const Matrix<T> &lhs){
        return this->Multiply(lhs);
    }
    // TODO
     void operator*=(const Matrix<T> &lhs){
        
    }
};