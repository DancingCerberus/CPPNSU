#include <iostream>
#include "Application.h"
#include "AppParameters.h"

int main(int argc, char *argv[]) {
  int const min_arguments_count = 3;
  if (argc < min_arguments_count) {
    std::cerr << "Not enough arguments" << std::endl;
    return 1;
  }

  std::vector<std::string> arguments(argc - 1);
  for (int i = 1; i < argc; ++i)
    arguments[i - 1] = argv[i];

  AppParameters parameters{
      .config_file_name = arguments[0],
      .output_file_name = arguments[1],
      .input_file_names = std::vector<std::string>(arguments.begin() + 2, arguments.end())
  };

  try {
    Application application(parameters);
    application.Run();
  }
  catch (...) {
    std::cerr << "Critical exception: Abort." << std::endl;
    return 1;
  }

  return 0;
}