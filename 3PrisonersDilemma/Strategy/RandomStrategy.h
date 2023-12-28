#pragma once

#include <random>
#include "IStrategy.h"

class RandomStrategy final : public IStrategy {
public:
    RandomStrategy();

    ~RandomStrategy() final = default;

    Choice GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) final;

    const std::string &GetName() final;

private:
    std::string name_;
    std::mt19937 mt_;
    std::uniform_int_distribution<int> dist_;
};