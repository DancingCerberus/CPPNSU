#include "StrategyFactory.h"
#include "StrategyEnum.h"
#include "VengefulStrategy.h"

std::unique_ptr<IStrategy> StrategyFactory::factory(StrategyEnum strategy) {
    switch (strategy) {
        case BetrayerEnum:
            return std::make_unique<BetrayerStrategy>();
        case CooperatorEnum:
            return std::make_unique<CooperatorStrategy>();
        case RandomEnum:
            return std::make_unique<RandomStrategy>();
        case VengefulEnum:
            return std::make_unique<VengefulStrategy>();
    }
}