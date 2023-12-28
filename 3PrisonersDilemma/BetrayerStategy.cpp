#include "AlwaysBetrayStrategy.h"

BetrayerStrategy::BetrayerStrategy() :
        name_("Always Betray") {}

Choice BetrayerStrategy::GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn ) {
    return D;
}

const std::string &BetrayerStrategy::GetName() {
    return name_;
}

