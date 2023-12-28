#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cassert>

template<typename String>
using Group = std::vector<String>;

template<typename String>
using Char = typename String::value_type;

template<typename String>
std::set<Char<String>> decomposeString(const String &str) {
  std::set<Char<String>> set_of_chars;
  for (auto c : str)
    set_of_chars.insert(c);
  return (set_of_chars);
}

template<typename String>
std::vector<Group<String>> GroupHeavyStrings(const std::vector<String> &strings) {
  std::map<std::set<Char<String>>, Group<String>> strings_by_chars;
  for (const auto &str : strings)
    strings_by_chars[decomposeString(str)].push_back(str);

  std::vector<Group<String>> to_return;
  to_return.reserve(strings_by_chars.size());

  std::transform(strings_by_chars.begin(), strings_by_chars.end(), std::back_inserter(to_return), [](const auto &pair) {
    return pair.second;
  });

  return std::move(to_return);
}

void TestGroupingABC() {
  std::vector<std::string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  assert(groups.size() == 2);
  sort(begin(groups), end(groups));
  assert(groups[0] == std::vector<std::string>({"caab", "abc", "bacc"}));
  assert(groups[1] == std::vector<std::string>({"cccc", "c"}));
}

void TestGroupingReal() {
  std::vector<std::string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  assert(groups.size() == 4);
  sort(begin(groups), end(groups));
  assert(groups[0] == std::vector<std::string>({"laptop", "paloalto"}));
  assert(groups[1] == std::vector<std::string>({"law", "wall", "awl"}));
  assert(groups[2] == std::vector<std::string>({"port"}));
  assert(groups[3] == std::vector<std::string>({"top", "pot"}));
}

int main() {
  TestGroupingABC();
  TestGroupingReal();
  return 0;
}