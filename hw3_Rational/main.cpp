#include <iostream>
#include <sstream>
using namespace std;

class Rational {
 public:
  Rational() : num_(0), denom_(1) {}
  Rational(int numerator, int denominator) {
    if (denominator == 0) {
      std::stringstream ss;
      ss << "Argument must not be zero";
      throw invalid_argument(ss.str());
    }

    num_ = numerator;
    denom_ = denominator;
  }

  ~Rational() = default;

  int Numerator() const {
    return num_;
  }
  int Denominator() const {
    return denom_;
  }

  Rational operator+(const Rational &other) {
    if (this->denom_ == other.denom_) {
      return {this->num_ + other.num_, denom_};
    } else {
      return {this->num_ * other.denom_ + other.num_ * this->denom_, this->denom_ * other.denom_};
    }
  }
  friend Rational operator*(const Rational &a, const Rational &b) {
    return {a.num_ * b.num_, a.denom_ * b.denom_};
  }
  friend Rational operator/(const Rational &a, const Rational &b) {
    return {a.num_ * b.denom_, a.denom_ * b.num_};
  }
  friend Rational operator-(const Rational &a, const Rational &b) {
    if (a.denom_ == b.denom_) {
      return {a.num_ - b.num_, a.denom_};
    } else {
      return {a.num_ * b.denom_ - b.num_ * a.denom_, a.denom_ * b.denom_};
    }
  }
  friend bool operator==(const Rational &a, const Rational &b) {
    return (a.num_ * b.denom_ == b.num_ * a.denom_);
  }
  friend ostream &operator<<(std::ostream &out, const Rational &a) {
    out << a.num_ << "/" << a.denom_;
    return out;
  }
  friend istream &operator>>(std::istream &in, Rational &a) {
    char slash;
    in >> a.num_ >> slash >> a.denom_;
    return in;
  }
 private:
  int num_, denom_;
};

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  Rational r1, r2;
  char operation;
  try {
    ss >> r1;
    ss.ignore(1);
    ss >> operation;
    ss.ignore(1);
    ss >> r2;
  } catch (exception &ex) {
    cout << "Invalid argument" << endl;
    return 1;
  }
  try {
    switch (operation) {
      case '+': {
        cout << r1 + r2;
        break;
      }
      case '-': {
        cout << r1 - r2;
        break;
      }
      case '*': {
        cout << r1 * r2;
        break;
      }
      case '/': {
        cout << r1 / r2;
        break;
      }
      case '=': {
        cout << (r1 == r2);
        break;
      }

      default: {
        cout << "Invalid operation" << endl;
      }
    }
  }
  catch (exception &ex) {
    cout << "Division by zero" << endl;
    return 2;
  }

  return 0;
}