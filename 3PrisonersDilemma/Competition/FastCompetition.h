#pragma once

#include <array>
#include "ICompetition.h"
#include "../Strategy/StrategyEnum.h"
#include "../Strategy/IStrategy.h"
#include "../Strategy/StrategyFactory.h"
#include <iostream>

class FastCompetition final : public ICompetition {
public:
    FastCompetition(const std::array<StrategyEnum, 3> &strategies, ReferenceTable reference_table, int steps);

    ~FastCompetition() final = default;

    void Simulation() final;

    const std::array<int, 3> &GetResults();

private:
    std::array<std::unique_ptr<IStrategy>, 3> strategies_;
    ReferenceTable reference_table_;
    int steps_;

    MoveTable move_table_;
    ScoreTable score_table_;
};