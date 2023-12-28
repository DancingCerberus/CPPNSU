#pragma once

#include "IStrategy.h"

class VengefulStrategy final : public IStrategy{
public:
    VengefulStrategy();

    ~VengefulStrategy() final = default;

    Choice GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) final;

    const std::string &GetName() final;

private:
    std::string name_;
};


