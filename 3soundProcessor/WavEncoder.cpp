#include <string>
#include "WavEncoder.h"

struct WavHeader {
  char riff_id[4]{0};
  int32_t chunk_size{0};
  char format[4]{0};
  char fmt_id[4]{0};
  int32_t fmt_sub_chunk_size{0};
  int16_t audio_format{0};
  int16_t num_channels{0};
  int32_t sample_rate{0};
  int32_t byte_rate{0};
  int16_t block_align{0};
  int16_t bits_per_sample{0};
  char data_id[4]{0};
  int32_t data_sub_chunk_size{0};
};

std::shared_ptr<Audio> WavEncoder::ReadAudio(std::istream &stream, std::string const &name) {
  auto header = WavHeader();

  stream.read((char *) &header, sizeof(header));

  size_t samplesCount = header.data_sub_chunk_size / sizeof(int16_t);
  auto audio = make_shared<Audio>(name, samplesCount);

  for (size_t i = 0; i < samplesCount; ++i)
    stream.read((char *) &audio->operator[](i), sizeof(int16_t));

  return audio;
}

void WavEncoder::WriteAudio(std::ostream &stream, const Audio &audio) {
  auto data_sub_chunk_size = static_cast<int32_t>(audio.SamplesCount() * sizeof(int16_t));
  int32_t fmt_sub_chunk_size = 16;
  WavHeader header{
      .riff_id{'R', 'I', 'F', 'F'},
      .chunk_size = 20 + data_sub_chunk_size + fmt_sub_chunk_size,
      .format{'W', 'A', 'V', 'E'},
      .fmt_id{'f', 'm', 't', ' '},
      .fmt_sub_chunk_size = fmt_sub_chunk_size,
      .audio_format = 1,
      .num_channels = 1,
      .sample_rate = 44100,
      .byte_rate = 88200,
      .block_align = 2,
      .bits_per_sample = 16,
      .data_id{'d', 'a', 't', 'a'},
      .data_sub_chunk_size = data_sub_chunk_size
  };

  stream.write((char *) &header, sizeof(header));

  for (size_t i = 0; i < audio.SamplesCount(); ++i)
    stream.write((char *) &audio[i], sizeof(audio[i]));
}