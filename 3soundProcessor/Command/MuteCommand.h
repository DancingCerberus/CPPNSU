#pragma once

#include "ICommand.h"

class MuteCommand : public ICommand {
 public:
  MuteCommand(int mute_from_sec, int mute_to_sec);

  void Run(std::weak_ptr<Audio> &audio_to_modify) override;

  std::string Description() override;

 private:
  int mute_from_sec_;

  int mute_to_sec_;
};