#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>

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

std::mutex countMutex;

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

    std::lock_guard<std::mutex> lock(countMutex); // Lock to ensure thread safety
    if (auto it = count_by_word.find(word); it != count_by_word.end())
      it->second += 1;
    else
      count_by_word.emplace(std::move(word), 1);

    word.clear();
  }
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  setlocale(LC_ALL, "rus");

  str input_file_name = "input.txt";
  str output_file_name = "output.csv";

  std::ifstream input_file(input_file_name);

  const int num_threads = std::thread::hardware_concurrency(); // Get the number of available threads
  std::vector<std::thread> threads;
  std::vector<std::unordered_map<str, int>> thread_count_by_word(num_threads);

  str line;
  int thread_id = 0;

  while (std::getline(input_file, line)) {
    threads.emplace_back(ParseString, std::ref(thread_count_by_word[thread_id]), std::move(line));
    thread_id = (thread_id + 1) % num_threads;
  }

  for (auto &thread : threads) {
    thread.join(); // Wait for all threads to finish
  }

  input_file.close();

  std::unordered_map<str, int> count_by_word;

  // Combine results from different threads
  for (const auto &thread_map : thread_count_by_word) {
    for (const auto &word_and_count : thread_map) {
      str word = word_and_count.first;
      count_by_word[word] += word_and_count.second;
    }
  }

  std::vector<WordStats> word_stats;

  for (auto &word_and_count : count_by_word) {
    str word = word_and_count.first;
    word_stats.emplace_back(std::move(word), word_and_count.second);
  }

  auto cmp = [](const WordStats &a, const WordStats &b) {
    return a.count_ > b.count_;
  };
  std::ranges::sort(word_stats, cmp);

  auto countSum = [](int a, const WordStats &b) { return a + b.count_; };

  int total_count = std::accumulate(word_stats.begin(), word_stats.end(), 0, countSum);

  auto fout = std::ofstream(output_file_name);

  for (auto &word_stat : word_stats)
    fout << word_stat.word_ << ", " << word_stat.count_ << ", " << word_stat.Percentage(total_count) << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  double time_taken =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

  time_taken *= 1e-9;

  std::cout << "Time taken by program is : " << std::fixed
            << time_taken << std::setprecision(9);
  std::cout << " sec" << std::endl;

  return 0;
}
