#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include "print_tuple.h"
#include "CSV_parser.h"

using namespace std;


int main() {
    /*std::tuple<int, int, float, char, bool> t(1, 2, 3.2, 's', false);
    std::cout << t;*/

    FileOnDemand input("test.csv");
    CSVParser<int, string> parser(input, ',', '\n', '"', 0);

//    FileOnDemand input("test.csv");
//    CSVParser<int, string> parser(input, '.', '|', '"', 0);

//    for (const tuple<int, string>& rs : (vector<tuple<int, string>>)parser) {
    for (const tuple<int, string>& rs : (vector<tuple<int, string>>)parser) {
        cout << rs;
        cout << endl;
    }

    return 0;
}
