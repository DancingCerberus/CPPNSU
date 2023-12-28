#pragma once

#include <string>
#include <vector>

struct AppParameters {
  std::string config_file_name;
  std::string output_file_name;
  std::vector<std::string> input_file_names;
};