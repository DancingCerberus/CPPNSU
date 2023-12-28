#include "InsertCommand.h"

#include <utility>

InsertCommand::InsertCommand(int insert_after_sec, std::weak_ptr<Audio> audio_to_insert) :
    insert_after_sec_{insert_after_sec},
    audio_to_insert_{std::move(audio_to_insert)} {}

void InsertCommand::Run(std::weak_ptr<Audio> &audio_to_modify) {
  auto &to_modify = *audio_to_modify.lock();
  auto &to_insert = *audio_to_insert_.lock();

  size_t insert_after_sample = insert_after_sec_ * to_modify.kSamples_per_second_;

  size_t end_of_new_block = insert_after_sample + to_insert.SamplesCount();

  if (end_of_new_block > to_modify.SamplesCount())
    to_modify.Extend(end_of_new_block + 1);

  for (size_t i = 0; i < to_insert.SamplesCount(); ++i)
    to_modify[insert_after_sample + i] = to_insert[i];
}

std::string InsertCommand::Description() {
  return "Insert " + audio_to_insert_.lock()->Name() + " after " + std::to_string(insert_after_sec_) + " seconds";
}