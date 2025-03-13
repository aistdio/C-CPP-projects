#include "s21_matrix_oop.h"

namespace s21 {

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows && cols) {
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  } else {
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  this->CopyMatrixValues(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { CleanUp(); }

void S21Matrix::CleanUp() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::SetRows(const int rows) {
  S21Matrix result(rows, cols_);
  if (rows > rows_) {
    result.rows_ = rows_;
  }
  result.CopyMatrixValues(*this);
  result.rows_ = rows;
  *this = std::move(result);
}

void S21Matrix::SetCols(const int cols) {
  S21Matrix result(rows_, cols);
  if (cols > cols_) {
    result.cols_ = cols_;
  }
  result.CopyMatrixValues(*this);
  result.cols_ = cols;
  *this = std::move(result);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;
  if (this->IsValid() && other.IsValid() && this->EqMatrixSize(other)) {
    for (int i = 0; i < rows_ && result; i++)
      for (int j = 0; j < cols_ && result; j++)
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) result = false;
  } else
    result = false;
  return result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  if (this->IsValid()) {
    for (int i = 0; i < cols_; i++)
      for (int j = 0; j < rows_; j++) result.matrix_[i][j] = matrix_[j][i];
  }
  return result;
}

double S21Matrix::Determinant() const {
  double result(0);
  if (this->IsValid() && rows_ == cols_ && !this->IsInfOrNan()) {
    if (rows_ == 1) {
      result = matrix_[0][0];
    } else if (rows_ == 2) {
      result = this->CalcDeterminant2x2();
    } else {
      S21Matrix tmp(*this);
      result = tmp.CalcUpperRowDeterminant(rows_);
    }
  } else {
    throw std::invalid_argument("recieved incorrect matrix");
  }
  return result;
}

double S21Matrix::CalcUpperRowDeterminant(int size) {
  double result = 0.0;
  if (size > 2) {
    double upper_determinant[size];
    S21Matrix subA(size - 1, size - 1);
    for (int col = 0; col < size; col++) {
      this->CalcSubMinor(subA, 0, col);
      upper_determinant[col] = subA.CalcUpperRowDeterminant(size - 1);
    }
    for (int i = 0; i < size; i++) {
      if (i % 2) matrix_[0][i] *= -1.0;
      result += matrix_[0][i] * upper_determinant[i];
    }
  } else {
    result = this->CalcDeterminant2x2();
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(rows_, cols_);
  if (this->IsValid() && rows_ == cols_ && !this->IsInfOrNan()) {
    if (rows_ == 1) {
      result.matrix_[0][0] = 1.0;
    } else {
      this->CalcMinor(result);
    }
  } else
    throw std::invalid_argument("recieved incorrect matrix");
  return result;
}

void S21Matrix::CalcMinor(S21Matrix& result) const {
  S21Matrix subA(rows_ - 1, cols_ - 1);
  for (int mrow = 0; mrow < rows_; mrow++) {
    for (int mcol = 0; mcol < cols_; mcol++) {
      this->CalcSubMinor(subA, mrow, mcol);
      result.matrix_[mrow][mcol] = subA.Determinant();
      if ((mrow + mcol) % 2 != 0) result.matrix_[mrow][mcol] *= -1;
    }
  }
}

void S21Matrix::CalcSubMinor(S21Matrix& subA, int mrow, int mcol) const {
  int rowXOR = 0, colXOR = 0;
  for (int row = 0; row < rows_ - 1; row++) {
    for (int col = 0; col < cols_ - 1; col++) {
      if (row == mrow) rowXOR = 1;
      if (col == mcol) colXOR = 1;
      subA.matrix_[row][col] = matrix_[row + rowXOR][col + colXOR];
    }
    colXOR = 0;
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result(rows_, cols_);
  if (this->IsValid() && rows_ == cols_ && !this->IsInfOrNan()) {
    double determinant = this->Determinant();
    if (determinant != 0.0)
      this->CalcInverseMatrix(result, determinant);
    else
      throw std::runtime_error("determinant of matrix is zero");
  } else
    throw std::invalid_argument("recieved incorrect matrix");
  return result;
}

void S21Matrix::CalcInverseMatrix(S21Matrix& result, double determinant) const {
  S21Matrix A_minor(this->CalcComplements());
  S21Matrix A_minor_transposed(A_minor.Transpose());
  A_minor_transposed.MulNumber(1.0 / determinant);
  result = std::move(A_minor_transposed);
}

bool S21Matrix::IsInfOrNan() const {
  bool returnValue = false;
  for (int i = 0; i < rows_ && !returnValue; i++)
    for (int j = 0; j < cols_ && !returnValue; j++)
      if (std::isinf(matrix_[i][j]) || std::isnan(matrix_[i][j]))
        returnValue = true;
  return returnValue;
}

void S21Matrix::CopyMatrixValues(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

void S21Matrix::AddNumber(const double num, const OperationType type) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (type == typePlus) {
        matrix_[i][j] += num;
      } else if (type == typeMult) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::ArithmeticOperations(const S21Matrix& other,
                                     const OperationType type) {
  if (!this->IsValid() || !other.IsValid() || this->IsInfOrNan() ||
      other.IsInfOrNan())
    throw std::invalid_argument("received incorrect value");

  if (type == typeMult && this->cols_ == other.rows_)
    this->CalcMul(other);
  else if (type != typeMult && this->EqMatrixSize(other))
    this->CalcSumSub(other, type);
  else
    throw std::invalid_argument("received incorrect size");

  if (this->IsInfOrNan())
    throw std::runtime_error("calculated value is INF or NAN");
}

void S21Matrix::CalcSumSub(const S21Matrix& other, const OperationType type) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (type == typePlus)
        matrix_[i][j] += other.matrix_[i][j];
      else if (type == typeMinus)
        matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::CalcMul(const S21Matrix& other) {
  S21Matrix result(rows_, other.cols_);
  for (int row1 = 0, row2 = 0; row1 < rows_; row1++, row2++)
    for (int col1 = 0, col3 = 0; col1 < other.cols_; col1++, col3++)
      for (int col2 = 0, row3 = 0; col2 < cols_; col2++, row3++)
        result.matrix_[row1][col1] +=
            matrix_[row2][col2] * other.matrix_[row3][col3];
  *this = std::move(result);
}

}  // namespace s21