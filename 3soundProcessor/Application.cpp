#include <iostream>
#include <sstream>
#include <map>
#include "Application.h"
#include "WavEncoder.h"
#include "Command/MuteCommand.h"
#include "Command/MixCommand.h"
#include "Command/InsertCommand.h"

void Application::ReadCommands(std::ifstream &config_stream) {
  for (std::string line; getline(config_stream, line);) {
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    for (std::string token; ss >> token;)
      tokens.push_back(token);

    if (tokens[0] == "mute") {
      commands_.push_back(std::make_unique<MuteCommand>(stoi(tokens[1]), stoi(tokens[2])));
      continue;
    }
    if (tokens[0] == "mix") {
      commands_.push_back(
          std::make_unique<MixCommand>(stoi(tokens[2]), GetAudioByIndex(stoi(tokens[1].substr(1)))));
      continue;
    }
    if (tokens[0] == "insert") {
      commands_.push_back(
          std::make_unique<InsertCommand>(stoi(tokens[2]), GetAudioByIndex(stoi(tokens[1].substr(1)))));
      continue;
    }
    throw std::invalid_argument("Unknown command name");
  }
}

void Application::ReadFiles(std::vector<std::string> &names) {
  for (auto &input_file_name: names) {
    try {
      std::ifstream stream(input_file_name);
      audio_pool_.push_back(WavEncoder::ReadAudio(stream, input_file_name));
      stream.close();
    }
    catch (std::exception &exception) {
      std::cerr << "Reading file " << input_file_name << " FAILED: " << std::endl << exception.what()
                << std::endl;
      throw;
    }
  }
  audio_to_modify_ = audio_pool_[0];
}

Application::Application(AppParameters &parameters) :
    audio_pool_{},
    commands_{},
    output_file_name_{parameters.output_file_name} {

  ReadFiles(parameters.input_file_names);

  try {
    std::ifstream config_stream(parameters.config_file_name);
    ReadCommands(config_stream);
    config_stream.close();
  }
  catch (std::exception &exception) {
    std::cerr << "Reading commands from " << parameters.config_file_name
              << " FAILED: " << std::endl << exception.what() << std::endl;
    throw;
  }
}

void Application::Run() {
  for (auto &command: commands_) {
    try {
      command->Run(audio_to_modify_);
    }
    catch (std::exception &exception) {
      std::cerr << "Command " << command->Description() << " execution FAILED: " << std::endl
                << exception.what() << std::endl;
      throw;
    }
  }

  try {
    std::ofstream stream(output_file_name_);
    WavEncoder::WriteAudio(stream, *audio_to_modify_.lock());
    stream.close();
  }
  catch (std::exception &exception) {
    std::cerr << "Writing output file to " << output_file_name_ << " FAILED: "
              << std::endl << exception.what() << std::endl;
    throw;
  }
}

bool Application::IsAudioIndexCorrect(size_t index) {
  return index < audio_pool_.size();
}

std::weak_ptr<Audio> Application::GetAudioByIndex(size_t index) {
  if (!IsAudioIndexCorrect(index))
    throw std::out_of_range("Index is out of audio pool range");
  return audio_pool_[index];
}