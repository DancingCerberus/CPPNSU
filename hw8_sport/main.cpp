#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>

int main() {
  std::string input_file_name = "input.txt";
  std::ifstream input_file(input_file_name);

  int n;

  input_file >> n;

  int number;
  int prev;

  std::list<int> players;
  std::unordered_map<int, std::list<int>::iterator> order;

  for (int i = 0; i < n; ++i) {
    input_file >> number >> prev;
    if (order.contains(prev)) {
      players.insert(order[prev], number);
      order[number] = std::prev(order[prev]);
    } else {
      players.push_back(number);
      order[number] = std::prev(players.end());
    }
  }

  for (const auto &player: players)
    std::cout << player << std::endl;

  return 0;
}
