#include <iostream>
#include <string>
#include <algorithm>

int main() {
  std::string phone_number;
  std::getline(std::cin, phone_number);

  if (phone_number[0] != '8' && !(phone_number[0] == '+' && phone_number[1] == '7')) {
    std::cout << "error" << std::endl;
    return 0;
  }

  phone_number.erase(std::remove_if(phone_number.begin(), phone_number.end(), ::isspace), phone_number.end());

  int opening_bracket{};
  int closing_bracket{};

  for (char c : phone_number) {
    if (opening_bracket > 1) {
      std::cout << "error" << std::endl;
      return 0;
    }

    if (c == '(')
      ++opening_bracket;

    if (c == ')')
      ++closing_bracket;

    if (closing_bracket > opening_bracket) {
      std::cout << "error" << std::endl;
      return 0;
    }
  }

  for (int i; i < phone_number.length() - 1; ++i)
    if (phone_number[i] == '-' && (phone_number[i] == phone_number[i + 1])) {
      std::cout << "error" << std::endl;
      return 0;
    }

  if (phone_number.starts_with('-') || phone_number.ends_with('-')) {
    std::cout << "error" << std::endl;
    return 0;
  }

  phone_number.erase(std::remove_if(phone_number.begin(), phone_number.end(), [](char c) {
    return !std::isdigit(c);
  }), phone_number.end());

  if (phone_number[0] == '8' || phone_number[0] == '7') {
    phone_number.replace(0, 1, "+7");
  }

  if (phone_number.length() != 12) {
    std::cout << "error" << std::endl;
    return 0;
  }

  std::cout << phone_number << std::endl;

  return 0;
}
