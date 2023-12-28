#pragma once

#include <vector>

#include "Date.h"

class Budget {
 private:
  Date period_begin_;
  std::vector<double> incomes_;

 public:
  Budget(Date const &period_begin, Date const &period_end);

  double &At(Date const &date);

  void Earn(Date &from, Date &to, double value);

  double Compute(Date &from, Date &to);

  ~Budget();
};