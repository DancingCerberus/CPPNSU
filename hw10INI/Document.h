#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

namespace Ini {
typedef std::unordered_map<std::string, std::string> Section;

class Document {
 public:
  Document();

  explicit Document(std::istream &input);

  Section &AddSection(const std::string &name);

  const Section &GetSection(const std::string &name) const;

  size_t SectionCount() const;

 private:
  std::unordered_map<std::string, Section> sections;
};

Document Load(std::istream &input);
}