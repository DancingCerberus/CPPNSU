#pragma once

#include "ICommand.h"

class InsertCommand : public ICommand {
 public:
  InsertCommand(int insert_after_sec, std::weak_ptr<Audio> audio_to_insert);

  void Run(std::weak_ptr<Audio> &audio_to_modify) override;

  std::string Description() override;

 private:
  int insert_after_sec_;
  std::weak_ptr<Audio> audio_to_insert_;
};