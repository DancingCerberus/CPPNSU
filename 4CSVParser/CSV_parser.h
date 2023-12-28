#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include <charconv>
#include <algorithm>

using namespace std;

class File {
 private:
  ifstream file;

 public:
  explicit File(const string &filename) : file(filename) {}

  istream &read(string &line, char del) {
    return getline(file, line, del);
  }
};

class FileFrom {
  std::string name;
  File *file;
 public:
  explicit FileFrom(std::string name) : name(std::move(name)), file(nullptr) {}
  ~FileFrom() {
    delete file;
  }

  File *operator->() {
    if (!file) {
      file = new File(name);
    }
    return file;
  }
};

template<int I, int Max, typename... Args>
struct B;
template<int I, int Max, typename... Args>
struct B : B<I + 1, Max, Args...> {
  static void a(vector<string> vec, tuple<Args...> t, tuple<Args...> *b) {
    typeof(get<I>(t)) type;
    stringstream ss(vec[I]);

    if constexpr (is_same_v<typename tuple_element<I, decltype(t)>::type, string>) {
      get<I>(*b) = vec[I];
    } else {
      if (!(ss >> std::noskipws >> type)) {
        throw runtime_error("Incorrect Type");
      } else {
        get<I>(*b) = type;
      }
    }
    B<I + 1, Max, Args...>::a(vec, t, b);
  }
};

template<int Max, typename... Args>
struct B<Max, Max, Args...> {
  static void a(const vector<string> &vec, tuple<Args...> t, tuple<Args...> *b) {}
};

template<int Count, typename... Args>
void out(vector<string> vec, tuple<Args...> t, tuple<Args...> *b) {
  B<0, Count, Args...>::a(vec, t, b);
}

template<typename... Args>
class CSVParser {
 private:
  vector<tuple<Args...>> strings;

 public:
  CSVParser(FileFrom &in, char col_del, char row_del, char scr, int countLines) {
    string a;
    for (int i = 0; in->read(a, row_del); i++) {
      if (i >= countLines) {
        strings.push_back(Parser(a, col_del, row_del, scr, i));
      }
    }
  }

  tuple<Args...> Parser(string str, char col_del, char row_del, char scr, int row) {
    str = col_del + str + row_del;
    string resStr;
    string token;
    vector<string> tokens;
    tuple<Args...> res;
    bool flag = false;
    for (int i = 1; i < str.size() - 1; i++) {
      if (str[i] == scr && !flag) {
        if (str[i - 1] == col_del) {
          flag = true;
        } else throw runtime_error("Incorrect format");
      } else if (str[i] == scr && flag) {
        if (str[i + 1] == col_del || str[i + 1] == row_del) {
          flag = false;
        } else throw runtime_error("Incorrect format");
      } else if ((str[i] == col_del || str[i] == row_del) && flag) {
        resStr.push_back(scr);
      } else resStr.push_back(str[i]);
    }

    stringstream ss(resStr);
    while (getline(ss, token, col_del)) {
      replace(token.begin(), token.end(), scr, col_del);
      tokens.push_back(token);
    }

    out<sizeof...(Args), Args...>(tokens, res, &res);

    return res;
  }

  explicit operator vector<tuple<Args...>>() const {
    return strings;
  }
};