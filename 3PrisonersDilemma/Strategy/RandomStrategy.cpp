#include "RandomStrategy.h"

RandomStrategy::RandomStrategy() :
        name_("Random"), mt_(std::random_device{}()), dist_(0, 1) {}

Choice RandomStrategy::GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) {
    return static_cast<Choice>(dist_(mt_));
}

const std::string &RandomStrategy::GetName() {
    return name_;
}