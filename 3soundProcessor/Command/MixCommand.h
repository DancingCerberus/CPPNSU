#pragma once

#include "ICommand.h"

class MixCommand : public ICommand {
 public:
  MixCommand(int mix_after_sec, std::weak_ptr<Audio> audio_to_mix_with);

  void Run(std::weak_ptr<Audio> &audio_to_modify) override;

  std::string Description() override;

 private:
  int mix_after_sec_;
  std::weak_ptr<Audio> audio_to_mix_with_;
};