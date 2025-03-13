#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <stdexcept>

namespace s21 {

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

 public:
  int GetRows() const;
  int GetCols() const;
  double** GetMatrix() const;
  void SetRows(const int rows);
  void SetCols(const int cols);
  void SetMatrixValue(const int row, const int col, const double value);
  void CleanUp();

 public:
  bool EqMatrix(const S21Matrix& other) const;
  void SumNumber(const double num);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

 public:
  bool IsValid() const;
  bool IsInfOrNan() const;
  void CopyMatrixValues(const S21Matrix& other);
  bool EqMatrixSize(const S21Matrix& other) const;

 public:
  S21Matrix operator+(const double num) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const double num) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator+=(const double num);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const double num);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  bool operator!=(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  double& operator()(const int i, const int j) const;

 private:
  int rows_, cols_;
  double** matrix_;

 private:
  enum OperationType { typePlus, typeMinus, typeMult };

 private:
  void AddNumber(const double num, const OperationType type);
  void ArithmeticOperations(const S21Matrix& other, const OperationType type);
  void CalcSumSub(const S21Matrix& other, const OperationType type);
  void CalcMul(const S21Matrix& other);
  double CalcUpperRowDeterminant(int size);
  double CalcDeterminant2x2() const;
  void CalcMinor(S21Matrix& result) const;
  void CalcSubMinor(S21Matrix& subA, int mrow, int mcol) const;
  void CalcInverseMatrix(S21Matrix& result, double determinant) const;
};

}  // namespace s21

namespace s21 {

inline int S21Matrix::GetRows() const { return rows_; }

inline int S21Matrix::GetCols() const { return cols_; }

inline double** S21Matrix::GetMatrix() const { return matrix_; }

inline void S21Matrix::SetMatrixValue(const int row, const int col,
                                      const double value) {
  matrix_[row][col] = value;
}

inline void S21Matrix::SumNumber(const double num) {
  if (rows_ && cols_) this->AddNumber(num, typePlus);
}

inline void S21Matrix::SumMatrix(const S21Matrix& other) {
  this->ArithmeticOperations(other, typePlus);
}

inline void S21Matrix::SubMatrix(const S21Matrix& other) {
  this->ArithmeticOperations(other, typeMinus);
}

inline void S21Matrix::MulNumber(const double num) {
  if (rows_ && cols_) this->AddNumber(num, typeMult);
}

inline void S21Matrix::MulMatrix(const S21Matrix& other) {
  this->ArithmeticOperations(other, typeMult);
}

inline double S21Matrix::CalcDeterminant2x2() const {
  double result =
      (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  return result;
}

inline bool S21Matrix::IsValid() const {
  return (matrix_ != nullptr && rows_ > 0 && cols_ > 0);
}

inline bool S21Matrix::EqMatrixSize(const S21Matrix& other) const {
  return (cols_ == other.cols_ && rows_ == other.rows_);
}

inline S21Matrix S21Matrix::operator+(const double num) const {
  S21Matrix result(*this);
  result.SumNumber(num);
  return result;
}

inline S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

inline S21Matrix S21Matrix::operator-(const double num) const {
  S21Matrix result(*this);
  result.SumNumber(-num);
  return result;
}

inline S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

inline S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

inline S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

inline S21Matrix& S21Matrix::operator+=(const double num) {
  this->SumNumber(num);
  return *this;
}

inline S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

inline S21Matrix& S21Matrix::operator-=(const double num) {
  return *this += -num;
}

inline S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

inline S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

inline S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

inline bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

inline bool S21Matrix::operator!=(const S21Matrix& other) const {
  return !this->EqMatrix(other);
}

inline S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  S21Matrix copy(other);
  *this = std::move(copy);

  return *this;
}

inline S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this == &other) {
    return *this;
  }

  this->CleanUp();
  std::swap(matrix_, other.matrix_);
  rows_ = other.rows_;
  cols_ = other.cols_;

  return *this;
}

inline double& S21Matrix::operator()(const int i, const int j) const {
  if (i < 0 || i > rows_ - 1 || j < 0 || j > cols_ - 1) {
    throw std::out_of_range("index is out of range");
  }

  return this->matrix_[i][j];
}

}  // namespace s21

#endif  // S21_MATRIX_H_