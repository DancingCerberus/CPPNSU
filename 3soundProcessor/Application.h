#pragma once

#include <memory>

#include "Audio.h"
#include "AppParameters.h"
#include "Command/ICommand.h"

class Application {
 public:
  explicit Application(AppParameters &parameters);

  void Run();

  bool IsAudioIndexCorrect(size_t index);

  std::weak_ptr<Audio> GetAudioByIndex(size_t index);

  void ReadFiles(std::vector<std::string> &names);

  void ReadCommands(std::ifstream &config_stream);

 private:
  std::vector<std::shared_ptr<Audio>> audio_pool_;
  std::vector<std::unique_ptr<ICommand>> commands_;
  std::weak_ptr<Audio> audio_to_modify_;
  std::string output_file_name_;
};