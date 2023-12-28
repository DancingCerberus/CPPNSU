#include <iostream>
#include <cassert>
#include <map>
#include <vector>

template<class T, T default_value>
class Matrix {
 public:
  Matrix() :
      body_{} {
  }

  class Element {
   public:
    Element(Matrix &matrix, size_t row, size_t column) :
        matrix_{matrix},
        row_{row},
        column_{column} {
    }

    operator T() const {
      auto index = std::make_pair(row_, column_);
      if (matrix_.body_.contains(index))
        return matrix_.body_.at(index);

      return default_value;
    }

    Element &operator=(T value) {
      if (value == default_value)
        return *this;

      auto index = std::make_pair(row_, column_);
      matrix_.body_[index] = std::forward<T>(value);
      return *this;
    }

   private:
    Matrix &matrix_;

    size_t row_;

    size_t column_;
  };

  Element operator()(size_t row, size_t column) {
    return Element(*this, row, column);
  }

  size_t size() const {
    return body_.size();
  }

  std::vector<Element> GetNonDefaultElems() {
    std::vector<Element> elems;
    for (auto &key_value : body_)
      elems.emplace_back(*this, key_value.first.first, key_value.first.second);
    return elems;
  }

 private:
  std::map<std::pair<size_t, size_t>, T>
      body_;
};

int main() {
  constexpr int defaultElement = -1;
  Matrix<int, defaultElement> matrix;

  assert(matrix.size() == 0); // все ячейки свободны
  auto a = matrix(0, 0);
  assert(a == -1);
  assert(matrix.size() == 0);
  matrix(100, 100) = 314;
  assert(matrix(100, 100) == 314);
  assert(matrix.size() == 1);

  int N = 10;
  for (int i = 0; i < N; i++) {
    matrix(i, i) = i;
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
      std::cout << matrix(i, j) << " ";

    std::cout << std::endl;
  }


  return 0;
}