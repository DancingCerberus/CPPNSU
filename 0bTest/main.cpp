#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <ranges>

using str = std::string;

struct WordStats {
  WordStats(str &&word, int count) :
      word_(word),
      count_(count) {
  }

  str word_;
  int count_;

  double Percentage(int total_count) const {
    return count_ * 100. / total_count;
  }
};

void ParseString(std::unordered_map<str, int> &count_by_word, str &&line) {
  line.push_back(' ');
  str word;
  for (char symbol : line) {
    if (isalpha(symbol) || isalnum(symbol)) {
      word.push_back(char(tolower(symbol)));
      continue;
    }
    if (word.empty())
      continue;

    if (auto it = count_by_word.find(word); it != count_by_word.end())
      it->second += 1;
    else
      count_by_word.emplace(std::move(word), 1);

    word.clear();
  }
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "rus");

  if (argc != 3)
    throw std::invalid_argument("Invalid argument count.");

  str input_file_name = argv[1];
  str output_file_name = argv[2];

  std::ifstream input_file(input_file_name);

  std::unordered_map<str, int> count_by_word;
  str line;

  while (std::getline(input_file, line))
    ParseString(count_by_word, std::move(line));

  input_file.close();

  std::vector<WordStats> word_stats;

  for (auto &word_and_count : count_by_word) {
    str word = word_and_count.first;
    word_stats.emplace_back(std::move(word), word_and_count.second);
  }

  auto cmp = [](const WordStats &a, const WordStats &b) {
    return a.count_ > b.count_;
  };
  std::ranges::sort(word_stats, cmp);

  int total_count = std::accumulate(word_stats.begin(), word_stats.end(), 0,
                                    [](int a, const WordStats &b) {
                                      return a + b.count_;
                                    });

  auto fout = std::ofstream(output_file_name);

  for (auto &word_stat : word_stats)
    fout << word_stat.word_ << ", " << word_stat.count_ << ", " << word_stat.Percentage(total_count) << std::endl;

  return 0;
}
