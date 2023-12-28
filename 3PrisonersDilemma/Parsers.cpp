#include "Parsers.h"

const std::unordered_map<std::string, StrategyEnum> Parsers::StrategyParser{
    {"Betrayer", BetrayerEnum},
    {"Cooperator", CooperatorEnum},
    {"Random", RandomEnum},
    {"Vengeful", VengefulEnum}};

const std::unordered_map<std::string, CompetitionEnum> Parsers::ModeParser{
    {"--mode=detailed", Detailed},
    {"--mode=fast", Fast},
    {"--mode=tournament", Tournament}};

std::vector<StrategyEnum> Parsers::ParseStrategies(const std::vector<std::string> &arguments) {
  std::vector<StrategyEnum> result;
  for (int i{}; i < arguments.size(); i++) {
    if (StrategyParser.find(arguments[i]) == StrategyParser.end())
      continue;
    result.push_back(StrategyParser.at(arguments[i]));
  }
  if (result.size() < 3)
    throw std::runtime_error("Not enough strategies");
  return result;
}

CompetitionEnum Parsers::ParseCompetition(const std::vector<std::string> &arguments) {
  for (int i{}; i < arguments.size(); i++)
    if (ModeParser.find(arguments[i]) != ModeParser.end())
      return ModeParser.at(arguments[i]);
  return Defaults::GetDefaultCompetition();
}

int Parsers::ParseSteps(const std::vector<std::string> &arguments) {
  for (int i{}; i < arguments.size(); i++)
    if (arguments[i].starts_with("--steps="))
      return std::stoi(arguments[i].substr(8));
  return Defaults::GetDefaultSteps();
}

ReferenceTable Parsers::ParseMatrix(const std::vector<std::string> &arguments) {
  for (int i{}; i < arguments.size(); i++)
    if (arguments[i].starts_with("--matrix=")) {
      std::ifstream input_stream(arguments[i].substr(9));
      if (!input_stream)
        throw std::runtime_error("Matrix file not found");
      ReferenceTable matrix;
      std::array<std::array<int, 3>, 8> raw_matrix{};
      for (int y{}; y < 8; y++)
        for (int x{}; x < 3; x++)
          if (!(input_stream >> raw_matrix[y][x]))
            throw std::runtime_error("Wrong matrix format");
      matrix[C][C][C] = raw_matrix[0];
      matrix[C][C][D] = raw_matrix[1];
      matrix[C][D][C] = raw_matrix[2];
      matrix[D][C][C] = raw_matrix[3];
      matrix[C][D][D] = raw_matrix[4];
      matrix[D][C][D] = raw_matrix[5];
      matrix[D][D][C] = raw_matrix[6];
      matrix[D][D][D] = raw_matrix[7];
      return matrix;
    }
  return Defaults::GetDefaultPointsTable();
}

