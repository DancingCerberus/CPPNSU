#include "VengefulStrategy.h"

VengefulStrategy::VengefulStrategy() :
    name_("Vengeful") {}

Choice VengefulStrategy::GetMove(const MoveTable &table, const ScoreTable &score_table, int place, int turn) {
  if (turn == 0)
    return C;
  switch (place) {
    case 0:
      if (table[turn - 1][1] == D || table[turn - 1][2] == D)
        return D;
      else
        return C;
    case 1:
      if (table[turn - 1][0] == D || table[turn - 1][2] == D)
        return D;
      else
        return C;
    case 2:
      if (table[turn - 1][0] == D || table[turn - 1][1] == D)
        return D;
      else
        return C;
  }

}

const std::string &VengefulStrategy::GetName() {
  return name_;
}
