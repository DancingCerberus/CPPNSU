#pragma once

#include "Strategy/IStrategy.h"

class BetrayerStrategy final : public IStrategy {
public:
    BetrayerStrategy();

    ~BetrayerStrategy() final = default;

    Choice GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) final;

    const std::string &GetName() final;

private:
    std::string name_;
};
