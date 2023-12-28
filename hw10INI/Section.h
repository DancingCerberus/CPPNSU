#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Section {
 public:
  Section();

  explicit Section(const std::string &name);

  Section(std::string, std::unordered_map<std::string, std::string>);

 private:
  std::unordered_map<std::string, std::string> records;
};