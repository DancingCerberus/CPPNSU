#pragma once

#include <string>
#include <array>
#include <vector>
#include "Choice.h"

using MoveTable = std::vector<std::array<Choice, 3>>;
using ReferenceTable = std::array<std::array<std::array<std::array<int, 3>, 2>, 2>, 2>;
using ScoreTable = std::vector<std::array<int, 3>>;

class IStrategy {
public:
    virtual ~IStrategy() = default;

    virtual Choice GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int step) = 0;

    virtual const std::string &GetName() = 0;
};


