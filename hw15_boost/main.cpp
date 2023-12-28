#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file" << std::endl;
    return 1;
  }


  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
  boost::char_separator<char> sep(" \t\n\r.,;!?-");
  tokenizer tokens(content, sep);


  std::map<std::string, int> wordFrequency;
  for (const auto& token : tokens) {
    std::string word = token;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);


    wordFrequency[word]++;
  }

  std::cout << "Word frequencies in the file:" << std::endl;
  for (const auto& pair : wordFrequency) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  return 0;
}
