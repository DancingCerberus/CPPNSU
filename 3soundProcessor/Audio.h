#pragma once

#include <vector>
#include <cstdint>
#include <memory>

class Audio {
 public:
  explicit Audio(std::string name, size_t samples_count);

  int16_t &operator[](size_t position);

  int16_t const &operator[](size_t position) const;

  size_t SamplesCount() const;

  void Extend(size_t new_size);

  std::string Name() const;

  int const kSamples_per_second_ = 44100;

 private:
  std::string name_;
  std::vector<int16_t> samples_;
};