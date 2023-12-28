#pragma once

#include <sstream>
#include <fstream>

typedef struct WAV_HEADER {
  char chunkId[4];         // RIFF Header
  unsigned int ChunkSize;          // RIFF Chunk Size
  char format[4];          // WAVE Header
  char subchunk1ID[4];     // fmt header
  unsigned int subchunk1Size;      // Size of the fmt chunk
  unsigned short audioFormat;        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
  unsigned short numChannels;        // Number of channels 1=Mono 2=Sterio
  unsigned int sampleRate;         // Sampling Frequency in Hz
  unsigned int byteRate;           // bytes per second
  unsigned short blockAlign;         // 2=16-bit mono, 4=16-bit stereo
  unsigned short bitsPerSample;      // Number of bits per sample
  char subchunk2ID[4];     // "data"  string
  unsigned int subchunk2Size;      // Sampled data length

} wav_hdr;

class WAV_file {
 private:
  wav_hdr header_;
  char *data_;
  long long length_;
 public:
  WAV_file() = default;

  std::stringstream read_from_file(char *input_file) {
    std::ifstream input(input_file, std::ios::binary);

    if (!input.is_open()) {
      throw "open_error";
    }

    input.read(reinterpret_cast<char *>(&header_), sizeof(wav_hdr));
    data_ = new char[header_.subchunk2Size + 6];
    input.read(data_, header_.subchunk2Size + 6);

    long long sample;
    std::stringstream res;
    input.read(reinterpret_cast<char *>(&sample), 2);
    while (!input.eof()) {
      length_ += 2;
      res.write(reinterpret_cast<char *>(&sample), 2);
      input.read(reinterpret_cast<char *>(&sample), 2);
    }

    input.close();
    return res;
  }

  void write_to_file(char *output_file, wav_hdr header, char *data, std::stringstream &res) {
    std::ofstream output(output_file, std::ios::binary);

    if (!output.is_open()) {
      throw "open_error";
    }

    output.write(reinterpret_cast<char *>(&header), sizeof(wav_hdr));
    output.write(data, header.subchunk2Size + 6);

    long long sample;
    res.read(reinterpret_cast<char *>(&sample), 2);
    while (!res.eof()) {
      output.write(reinterpret_cast<char *>(&sample), 2);
      res.read(reinterpret_cast<char *>(&sample), 2);
    }

    output.close();
    res.clear();
  }

  int len() {
    return length_;
  }

  char *data() {
    return data_;
  }

  wav_hdr header() {
    return header_;
  }
};
