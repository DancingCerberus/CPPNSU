#pragma once

#include <iostream>
#include "ICompetition.h"
#include "../Strategy/StrategyFactory.h"

class DetailedCompetition final : public ICompetition {
public:
    DetailedCompetition(const std::array<StrategyEnum, 3> &strategies, ReferenceTable reference_table);

    ~DetailedCompetition() final = default;

    void Simulation() final;

private:
    std::array<std::unique_ptr<IStrategy>, 3> strategies_;
    ReferenceTable reference_table_;

    MoveTable move_table_;
    ScoreTable points_table_;
};
