#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "Audio.h"

class WavEncoder {
 public:
  static std::shared_ptr<Audio> ReadAudio(std::istream &steam, std::string const &name);

  static void WriteAudio(std::ostream &steam, Audio const &audio);
};