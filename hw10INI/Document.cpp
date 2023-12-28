#include "Document.h"

Ini::Document::Document() = default;

Ini::Document::Document(std::istream &input) {
  std::string line;
  Section *section;
  while (std::getline(input, line)) {
    if (line.empty() || line[0] == ';')
      continue;

    if ((line[0] == '[') && (line[line.size() - 1] == ']')) {
      section = &AddSection(line.substr(1, line.length() - 2));
      continue;
    }

    std::size_t delimiterPos = line.find('=');
    if (delimiterPos != std::string::npos)
      section->insert({line.substr(0, delimiterPos), line.substr(delimiterPos + 1)});
  }
}

Ini::Section &Ini::Document::AddSection(const std::string &name) {
  return sections[name];
}

const Ini::Section &Ini::Document::GetSection(const std::string &name) const {
  return sections.at(name);
}

size_t Ini::Document::SectionCount() const {
  return sections.size();
}

Ini::Document Ini::Load(std::istream &input) {
  return Ini::Document(input);
}