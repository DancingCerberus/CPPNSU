#include <iostream>

#include "Budget.h"

void ProcessEarnQuery(Budget &budget) {
  Date from;
  Date to;
  int value;
  std::cin >> from >> to >> value;

  budget.Earn(from, to, value);
}

void ProcessComputeQuery(Budget &budget) {
  Date from;
  Date to;
  std::cin >> from >> to;

  double income = budget.Compute(from, to);
  std::cout << income << std::endl;
}

void ProcessQuery(Budget &budget) {
  static const std::string earn_command = "Earn";
  static const std::string compute_command = "ComputeIncome";

  std::string command;
  std::cin >> command;

  if (command == earn_command)
    ProcessEarnQuery(budget);
  else if (command == compute_command)
    ProcessComputeQuery(budget);
  else
    std::cout << "Unknown command: " << command << std::endl;
}

int main() {
  Date period_begin(2000, 1, 1);
  Date period_end(2099, 12, 31);

  Budget budget(period_begin, period_end);

  int queries_count;
  std::cin >> queries_count;

  for (int i = 0; i < queries_count; ++i)
    ProcessQuery(budget);

  return 0;
}