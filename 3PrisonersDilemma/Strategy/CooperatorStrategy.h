#pragma once

#include "IStrategy.h"

class CooperatorStrategy final : public IStrategy {
 public:
  CooperatorStrategy();

  ~CooperatorStrategy() final = default;

  Choice GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) final;

  const std::string &GetName() final;

 private:
  std::string name_;
};