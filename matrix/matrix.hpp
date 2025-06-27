#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>

const float EPSOLON_ = 0.000001;
template <typename T>
class Matrix {
    
    std::vector<std::vector<T>> matrix_;
    int row_len = 0;
    int col_len = 0;

    void checkSize(std::pair<int,int> &rhs_pair) const {
        if(rhs_pair.first!= row_len || rhs_pair.second != col_len) {
            throw std::runtime_error("matrixs must be of same size");
        }
    }

    
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
       if (row < 0 || row >= row_len || col < 0 || col >= col_len) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return matrix_[row][col];
    }

    const T& at(int row, int col) const {
        if (row < 0 || row >= row_len || col < 0 || col >= col_len) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return matrix_.at(row).at(col);
    }

    // TODO
    void insertRow(std::vector<T> newRow){};
    // TODO
    void insertColumn(std::vector<T> newCol){};

    // TODO
    void remove(){};

    bool isEqual(Matrix<T> const rhs) const{
        auto rhs_pair = rhs.size();
        if (rhs_pair.first != row_len || rhs_pair.second != col_len) return false;

        for (int i = 0;i < row_len; i++ ){
            for(int ii = 0; ii < col_len; ii++){
                if (std::fabs(this->at(i,ii) - rhs.at(i,ii)) >= EPSOLON_) return false;
            }
        }
        return true;
    }
    // properties
    bool isSquare() const {
        return row_len == col_len;
    }
    
    bool isSymmetric() const {
        return this->isEqual(this->Transpose());
    }
    
    T determinant() const {
        
    }
    // Artithmetic 
    void addInPlace(Matrix<T> const &rhs){
        checkSize(rhs.size());
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix_[i][ii] += rhs.at(i,ii);
            }
        }
        
    };

    void subtractionInPlace(Matrix<T> const &rhs){
        checkSize(rhs.size());
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                matrix_[i][ii] -= rhs.at(i,ii);
            }
        }
    };
  
    void ScalarMultiplicationInPlace(const T &lhs){
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                this->at(i,ii) *= lhs;
            }
        }
    };

    Matrix<T> add(Matrix<T> const &rhs) const{
        checkSize(rhs.size());
        Matrix<T> result(row_len,col_len);
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                result.at(i,ii) = this->at(i,ii) + rhs.at(i,ii);
            }
        }
        return result;
    }

    Matrix<T> subtract(Matrix<T> const &rhs) const{
        checkSize(rhs.size());
        Matrix<T> result(row_len,col_len);
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                result.at(i,ii) =this->at(i,ii) - rhs.at(i,ii);
            }
        }
    }

    Matrix<T> ScalarMultiplication(const T &rhs) const{
        Matrix<T> result(row_len,col_len);
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                result.at(i,ii) = this->at(i,ii) * rhs;
            }
        }
        return result;
    }

    Matrix<T> Multiply(Matrix<T> const  &rhs) const{
        auto rhs_pair = rhs.size();
        checkSize(rhs_pair);

        Matrix<T> result(row_len,rhs_pair.second);
       for(int m1_row = 0; m1_row < row_len;m1_row++){
        for(int m2_col = 0; m2_col < rhs_pair.second; m2_col++){
            T sum = 0;
            for(int m1_col = 0; m1_col< col_len; m1_col++){
                sum += this->at(m1_row,m1_col) * rhs.at(m1_col,m2_col);
            }
            result.at(m1_row,m2_col) = sum;
        }
    }
    return result;
    };

    Matrix<T> hadamardProduct(const Matrix<T>& rhs) const {
        checkSize(rhs.size());
        Matrix<T> result(row_len,col_len);
        for(int i = 0; i < row_len; i++){
            for(int ii = 0; ii < col_len; ii++){
                result.at(i,ii) =this->at(i,ii) * rhs.at(i,ii);
            }
        }
    }
     // TODO
    Matrix<T> Transpose() const{
        Matrix<T> result(col_len, row_len);
        for (int i = 0; i < row_len; ++i) {
            for (int j = 0; j < col_len; ++j) {
                result.at(j, i) = this->at(i, j);
            }
        }
        return result;
    };
    
    
    Matrix<T> inverse(){};


    // arithmetic overloads
    void operator+=(const Matrix<T> &rhs){
        this->addInPlace(rhs);
    }

    template<typename Scalar>
    void operator*=(const Scalar &rhs){
        this->ScalarMultiplicationInPlace(rhs);
    }
    
     void operator*=(const Matrix<T> &rhs){
        
    }

    Matrix<T> operator+(const Matrix<T> &rhs) const{
        return this->add(rhs);
    }
    
    Matrix<T> operator-(const Matrix<T> &rhs) const{
        return this->subtract(rhs);
    }
    
    Matrix<T> operator*(const Matrix<T> &rhs) const{
        return this->Multiply(rhs);
    }

    template<typename Scalar>
    Matrix<T> operator*(const Scalar &rhs) const{
        return this->ScalarMultiplication(rhs);
    }

    // utility operatores
    bool operator==(const Matrix<T> &rhs) const {
        return this->isEqual(rhs);
    }
};


/*

// PROPERTIES

T determinant() const

T trace() const

int rank() const

bool isSingular() const

// transformation
Matrix<T> transposed() const

Matrix<T> inverse() const

Matrix<T> subMatrix(int rowStart, int rowEnd, int colStart, int colEnd) const

Matrix<T> minorMatrix(int row, int col) const  // used for determinant/cofactor

Matrix<T> adjugate() const

// Decompositions
std::pair<Matrix<T>, Matrix<T>> luDecompose() const

std::pair<Matrix<T>, Matrix<T>> qrDecompose() const

std::tuple<Matrix<T>, Matrix<T>, Matrix<T>> svd() const

std::pair<Matrix<T>, Matrix<T>> choleskyDecompose() const  // for symmetric positive definite

Matrix<T> eigenValues() const  // (for diagonalizable matrices)

Matrix<T> eigenVectors() const

// solve linear system
Matrix<T> solve(const Matrix<T>& b) const  // Solve Ax = b

Matrix<T> backSubstitute() const  // For upper triangular matrices

Matrix<T> forwardSubstitute() const

// norm and measures
T normL1() const     // sum of absolute values

T normL2() const     // Euclidean norm

T normInf() const    // max row sum

T frobeniusNorm() const
*/