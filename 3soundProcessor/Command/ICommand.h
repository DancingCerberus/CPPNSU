#pragma once

#include <memory>

#include "../Audio.h"

class ICommand {
 public:
  ICommand() = default;

  virtual void Run(std::weak_ptr<Audio> &audio_to_modify) = 0;

  virtual std::string Description() = 0;

  virtual ~ICommand() = default;
};