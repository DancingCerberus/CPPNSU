#include "CooperatorStrategy.h"

CooperatorStrategy::CooperatorStrategy() :
    name_("Cooperator") {}

Choice CooperatorStrategy::GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) {
  return C;
}

const std::string &CooperatorStrategy::GetName() {
  return name_;
}