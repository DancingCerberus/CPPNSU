#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "print_tuple.h"
#include "CSV_parser.h"

using namespace std;

int main() {
  cout << "Print tuple:" << endl;
  tuple<int, float, int, char, bool> sample(1, 2.1, 2, 'c', true);
  cout << sample;
  cout << endl;

  FileFrom standard_input("test_standard.csv");
  CSVParser<int, string> standard_parser(standard_input, ',', '\n', '"', 0);

  cout << "Parse CSV:" << endl;
  for (const tuple<int, string> &rs : (vector<tuple<int, string>>) standard_parser) {
    cout << rs;
    cout << endl;
  }

  return 0;
}
