#pragma once

#include <memory>
#include "../AlwaysBetrayStrategy.h"
#include "CooperatorStrategy.h"
#include "RandomStrategy.h"
#include "StrategyEnum.h"

class StrategyFactory {
public:
    static std::unique_ptr<IStrategy> factory(StrategyEnum strategy);
};