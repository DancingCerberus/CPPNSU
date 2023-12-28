#pragma once

#include <fstream>

class Date {
 private:
  int year_;
  int month_;
  int day_;

  static bool IsLeapYear(int year);

  static int GetMonthDuration(bool is_leap_year, int month);

  bool IsValid() const;

 public:
  Date();

  Date(int year, int month, int day);

  Date(Date const &other);

  Date &operator=(Date const &other);

  Date &operator++();

  bool operator<=(Date const &other) const;

  int operator-(Date const &other) const;

  std::string ToString() const;

  ~Date();

  friend std::istream &operator>>(std::istream &istream, Date &date);
};