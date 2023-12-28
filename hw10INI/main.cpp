#include "test.h"

int main() {
  TestLoadIni();
  TestDocument();
  TestUnknownSection();
  TestDuplicateSections();
  return 0;
}