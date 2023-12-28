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

  FileOnDemand standard_input("test_standard.csv");
  CSVParser<int, string> standard_parser(standard_input, ',', '\n', '"', 0);

  FileOnDemand alt_input("test_alt.csv");
  CSVParser<int, string> alt_parser(alt_input, '.', '|', '"', 0);

  cout << "Standard format:" << endl;
  for (const tuple<int, string> &rs : (vector<tuple<int, string>>) standard_parser) {
    cout << rs;
    cout << endl;
  }

  cout << "Alternative format:" << endl;

  for (const tuple<int, string> &rs : (vector<tuple<int, string>>) alt_parser) {
    cout << rs;
    cout << endl;
  }

  return 0;
}
