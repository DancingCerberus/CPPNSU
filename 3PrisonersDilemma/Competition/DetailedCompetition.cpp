#include "DetailedCompetition.h"

DetailedCompetition::DetailedCompetition(const std::array<StrategyEnum, 3> &strategies, ReferenceTable reference_table)
    :
    strategies_({StrategyFactory::factory(strategies[0]),
                 StrategyFactory::factory(strategies[1]),
                 StrategyFactory::factory(strategies[2])}),
    reference_table_(reference_table) {}

void DetailedCompetition::Simulation() {
  for (int turn{};; ++turn) {
    move_table_.push_back({strategies_[0]->GetMove(move_table_, points_table_, 0, turn),
                           strategies_[1]->GetMove(move_table_, points_table_, 1, turn),
                           strategies_[2]->GetMove(move_table_, points_table_, 2, turn)});
    const std::array<int, 3> &cur_step_results(reference_table_
                                               [move_table_[turn][0]]
                                               [move_table_[turn][1]]
                                               [move_table_[turn][2]]);
    if (turn == 0)
      points_table_.push_back(cur_step_results);
    else
      points_table_.push_back({points_table_[turn - 1][0] + cur_step_results[0],
                               points_table_[turn - 1][1] + cur_step_results[1],
                               points_table_[turn - 1][2] + cur_step_results[2]});

    std::cout << "Round " << turn + 1 << ":" << std::endl;
    for (int i{}; i < 3; i++)
      std::cout << "Strategy " << strategies_[i]->GetName()
                << " " << (move_table_[turn][i] ? "cooperates. " : "betrays. ")
                << "Points for current step: " << cur_step_results[i]
                << ". Overall points: " << points_table_[turn][i] << std::endl;

    std::string line;
    std::getline(std::cin, line);
    if (line == "quit")
      break;
  }

}