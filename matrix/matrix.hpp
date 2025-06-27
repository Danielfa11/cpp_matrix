#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>

template <typename T>
class Matrix {
    
    std::vector<std::vector<T>> matrix_;
    int row_len = 0;
    int col_len = 0;

    void checkSize(std::pair<int,int> rhs_pair) const {
        if(rhs_pair.first!= row_len || rhs_pair.second != col_len) {
            throw std::runtime_error("Matrixs must be of same size in checkSize");
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

    /*
    get the size of the matrix nxm

    current method to access the values is:
    row_len = size.first
    col_len = size.second

    return type: std::pair<int,int>
    */
    std::pair<int,int> size() const{
        return std::make_pair(row_len,col_len);
    }

    /*
    Print the current matrix
    fromate is:
    1 2 3
    4 5 6
    7 8 9

    return type: void
    */
    void const print(){
        for(int i =0; i< row_len;i++){
            for(int ii = 0;ii< col_len;ii++){
                std::cout << matrix_[i][ii] << " ";
            }
            std::cout << "\n";
        }
    }
    
    T& at(int row, int col) {
       if (row < 0 || row >= row_len || col < 0 || col >= col_len) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return matrix_.at(row).at(col);
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

    /*
    compairs the matrixs element wise where differance bewteen 
    value must be with in 0.000001

    return type:bool
    */
    bool isEqual(Matrix<T> const rhs) const{
        auto rhs_pair = rhs.size();
        if (rhs_pair.first != row_len || rhs_pair.second != col_len) return false;

        const float EPSOLON_ = 0.000001;
        for (int i = 0;i < row_len; i++ ){
            for(int ii = 0; ii < col_len; ii++){
                if (std::fabs(this->at(i,ii) - rhs.at(i,ii)) >= EPSOLON_) return false;
            }
        }
        return true;
    }
    // properties

    /*
    if true is rows.lenght == cols.length

    return type: bool
    */
    bool isSquare() const {
        return row_len == col_len;
    }
    
    /*
    compairs the matrixs to its transpoed matrix 
    the equal comparison is true is all elements are within 0.000001 of each other 
    A = A^T is true
    A != A^T false

    return type: bool
    */
    bool isSymmetric() const {
        return this->isEqual(this->Transpose());
    }
    
    /*
    get the trace of a square matrix tr(A)

    When the matrix is not square throws error

    return type: T
    */
    T trace() const {
        if(!this->isSquare()){
            throw std::runtime_error("Matrix row and cols must be of same size");
        }

        T sum = 0;
        for(int i = 0; i < row_len;i++){
            sum+= this->at(i,i);
        }
        return sum;
    };

    T determinant() const {
        if(!isSquare()) {
            throw std::runtime_error("Matrix is not square and is rows: " + row_len +" and cols: "+ col_len);
        }

        
    }
    // Artithmetic 

    /*
    Adds the inputs matrix to the current one values

    return type:void 
    */
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
        if (rhs_pair.first != col_len){
            throw std::runtime_error("Must have the same row and column length");
        }

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
     
    // Transform

    /*
    Transpose the matrixs following general method of
    A^T

    return type: Matrix<T>
    */
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
    /*
    rowStart: 0 indexed 
    rowEnd: exclusive end i.e last idx+1  
    colStart: 0 indexed
    colEnd: exclusive end i.e last idx+1

    return type: Matrix<T>
    */
    Matrix<T> subMatrix(int rowStart, int rowEnd, int colStart, int colEnd) const{
        
        if(rowStart < 0 || rowEnd > row_len || colStart < 0 || colEnd > col_len ||  rowStart >= rowEnd || colStart >= colEnd){
            throw std::out_of_range("Matrix index out of bounds in subMatrix");
        }
        Matrix<T> result(rowEnd-rowStart, colEnd - colStart);

        for(int i = rowStart; i < rowEnd; i++){
            for(int ii = colStart; ii< colEnd; ii++){
                result.at(i-rowStart,ii-colStart) = this->at(i,ii);
            }
        }
        return result;
    }
    
    Matrix<T> apply(std::function<T(T)> func) const {
        Matrix<T> result(row_len, col_len);
        for (int i = 0; i < row_len; i++) {
            for (int j = 0; j < col_len; j++) {
                result.at(i,j) = func(this->at(i,j));
            }
        }
        return result;
    }
    
    void broadcastAddRows(const Matrix<T>& bias_row) {
        
        auto bias_pair = bias_row.size();
        if (bias_pair.first != 1 || bias_pair.second != col_len)
            throw std::runtime_error("Bias row must be shape 1×cols of matrix");

        for (int i = 0; i < row_len; ++i) {
            for (int ii = 0; ii < col_len; ++ii) {
                this->at(i,ii) += bias_row.at(0,ii);
            }
        }
}
    // arithmetic overloads operators
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

int rank() const

bool isSingular() const

// transformation

Matrix<T> inverse() const



  // used for determinant/cofactor

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