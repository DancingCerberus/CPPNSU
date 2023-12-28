class Document {
 public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

 private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);