#include <stdexcept>
#include <sstream>

#include "Date.h"

bool Date::IsLeapYear(int year) {
  return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int Date::GetMonthDuration(bool is_leap_year, int month) {
  switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: return 31;

    case 2: return is_leap_year ? 29 : 28;

    case 4:
    case 6:
    case 9:
    case 11: return 30;

    default: throw std::out_of_range("Month out of range: " + std::to_string(month));
  }
}

bool Date::IsValid() const {
  if (year_ < 1 || month_ < 1 || day_ < 1 || month_ > 12 || day_ > 31)
    return false;

  return day_ <= GetMonthDuration(IsLeapYear(year_), month_);
}

Date::Date() : year_(0), month_(0), day_(0) {
}

Date::Date(int year, int month, int day) :
    year_(year),
    month_(month),
    day_(day) {
  if (!IsValid())
    throw std::invalid_argument("Bad data");
}

Date::Date(Date const &other) = default;

Date &Date::operator=(Date const &other) = default;

Date &Date::operator++() {
  ++day_;

  if (day_ > GetMonthDuration(IsLeapYear(year_), month_)) {
    day_ = 1;
    ++month_;

    if (month_ > 12) {
      month_ = 1;
      ++year_;
    }
  }

  return *this;
}

bool Date::operator<=(const Date &other) const {
  if (year_ < other.year_)
    return true;
  if (year_ > other.year_)
    return false;

  if (month_ < other.month_)
    return true;
  if (month_ > other.month_)
    return false;

  if (day_ < other.day_)
    return true;
  if (day_ > other.day_)
    return false;

  return true;
}

int Date::operator-(const Date &other) const {
  bool is_correct = other <= *this;
  if (!is_correct)
    throw std::domain_error("Bad date difference");

  Date copy(other);

  int days = 0;
  while (copy <= *this) {
    ++copy;
    ++days;
  }

  return days - 1;
}

std::string Date::ToString() const {
  std::stringstream stream;
  stream << year_ << "-" << month_ << "-" << day_;
  return stream.str();
}

Date::~Date() = default;

std::istream &operator>>(std::istream &istream, Date &date) {
  istream >> date.year_;
  istream.ignore(256, '-');
  istream >> date.month_;
  istream.ignore(256, '-');
  istream >> date.day_;

  if (!date.IsValid())
    throw std::domain_error("Bad date in input: " + date.ToString());

  return istream;
}