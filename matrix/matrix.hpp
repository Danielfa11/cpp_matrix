#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class Matrix {
    
    std::vector<std::vector<T>> matrix;
    int row_len = 0;
    int col_len = 0;

    public:
    Matrix(int const &rows, int const &cols){
        matrix.resize(rows, std::vector<T>(cols));
        row_len = rows;
        col_len = cols;
    };
    
    Matrix(std::vector<T> const &vec, int const &rows, int const &cols){
        if (rows * cols  != vec.size()) {
            throw std::runtime_error("vector must have same size as col * rows");
        }

        matrix.resize(rows, std::vector<T>(cols));
        row_len = rows;
        col_len = cols;

        for(int i = 0; i< rows; i++){
            for(int ii = 0; ii < cols; ii++){
                matrix[i][ii] = vec[i * cols + ii];
            }
        }
    };

    std::pair<int,int> size() const{
        return std::make_pair(row_len,col_len);
    }

    void const print(){
        for(int i =0; i< row_len;i++){
            for(int ii = 0;ii< col_len;ii++){
                std::cout << matrix[i][ii] << " ";
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
        return matrix[row][col];
    }

    const T& at(int row, int col) const {
        return matrix.at(row).at(col);
    }


    void insertRow(std::vector<T> newRow){};

    void insertColumn(std::vector<T> newCol){};

    void remove(){};

    void addInPlace(Matrix<T> const &lhs){
        auto lhs_pair = lhs.size();
        if(lhs_pair.first != row_len || lhs_pair.second != col_len) {
            throw std::runtime_error("matrixs must be of same size");
        }
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix[i][ii] += lhs.at(i,ii);
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
                matrix[i][ii] -= lhs.at(i,ii);
            }
        }
    };

    void ScalarMultiplication(const int &lhs){
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix[i][ii] *= lhs;
            }
        }
    };
    void ScalarMultiplication(const double lhs){
         for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix[i][ii] *= lhs;
            }
        }
    };

    void Transpose(){};
    
    Matrix<T> inverse(){};
    Matrix<T> MatrixMultiple(Matrix<T> const  &lhs){};


    void operator+=(const Matrix<T> &lhs){
        this->addInPlace(lhs);
    }

    Matrix<T> operator+(const Matrix<T> &lhs){
        return this->add(lhs);
    }
};