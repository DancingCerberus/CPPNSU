#pragma once


#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <fstream>
#include "Strategy/StrategyEnum.h"
#include "Competition/CompetitionEnum.h"
#include "Defaults.h"

class Parsers {
public:
    const static std::unordered_map<std::string, StrategyEnum> StrategyParser;

    const static std::unordered_map<std::string, CompetitionEnum> ModeParser;

    static std::vector<StrategyEnum> ParseStrategies(const std::vector<std::string> &arguments);

    static CompetitionEnum ParseCompetition(const std::vector<std::string> &arguments);

    static int ParseSteps(const std::vector<std::string> &arguments);

    static ReferenceTable ParseMatrix(const std::vector<std::string> &arguments);
};
