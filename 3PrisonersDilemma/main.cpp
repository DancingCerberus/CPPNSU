#include <iostream>
#include <unordered_map>
#include "Strategy/StrategyFactory.h"
#include "Competition/CompetitionEnum.h"
#include "Competition/ICompetition.h"
#include "Competition/DetailedCompetition.h"
#include "Competition/FastCompetition.h"
#include "Competition/TournamentCompetition.h"
#include "Parsers.h"

int main(const int argc, const char *argv[]) {

  std::vector<std::string> arguments;

  CompetitionEnum mode;
  std::vector<StrategyEnum> strategies_vec;
  int steps;
  ReferenceTable matrix;

  for (int i = 1; i < argc; i++)
    arguments.emplace_back(argv[i]);

  if (arguments.size() < 3) {
    std::cout << "Not enough arguments" << std::endl;
    return 1;
  }

  try {
    strategies_vec = Parsers::ParseStrategies(arguments);
    mode = Parsers::ParseCompetition(arguments);
    steps = Parsers::ParseSteps(arguments);
    matrix = Parsers::ParseMatrix(arguments);
  }
  catch (const std::exception &ex) {
    std::cout << "Invalid input: " << ex.what() << std::endl;
    return 2;
  }

  std::unique_ptr<ICompetition> competition;
  std::array<StrategyEnum, 3> strategies_arr{strategies_vec[0], strategies_vec[1], strategies_vec[2]};
  switch (mode) {
    case Detailed:competition = std::make_unique<DetailedCompetition>(strategies_arr, matrix);
      break;
    case Fast:competition = std::make_unique<FastCompetition>(strategies_arr, matrix, steps);
      break;
    case Tournament:competition = std::make_unique<TournamentCompetition>(strategies_vec, matrix, steps);
      break;
  }
  competition->Simulation();
  return 0;
}
