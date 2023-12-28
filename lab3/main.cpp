#include <sstream>
#include <iostream>
#include <vector>
#include "configuration.h"
#include "converter.h"
#include "wav_file.h"

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cerr << "Usage: sound_processor  <config.txt>  <output.wav>  <input1.wav>  [ <input2.wav>  ... ]" << std::endl;
    return 1;
  }

  Config conf;

  try {
    conf.read_config(argv[1]);
  }
  catch (const char *exc) {
    if (exc[0] == 'f') {
      std::cerr << "Config file <" << argv[1] << "> format is not .txt\n";
      return 2;
    } else if (exc[0] == 'o') {
      std::cerr << "Error opening config file <" << argv[1] << ">\n";
      return 3;
    } else if (exc[0] == 'e') {
      std::cerr << "Converter start and finish points are equal, has no effect\n";
    } else if (exc[0] == 'n') {
      std::cerr << "Start or finish point is negative\n";
      return -1;
    } else if (exc[0] == 'l') {
      std::cerr << "Finish point is less than start\n";
      return 4;
    }
  }

  int work = conf.how_much_work();
  Converter *conv;
  WAV_file input, output;
  std::stringstream stream = input.read_from_file(argv[3]);

  for (int i = 0; i < work; i++) {
    operation current_oper = conf.what_to_do(i);
    current_oper.sampleRate = (input.header()).sampleRate;

    switch (current_oper.operation_type) {
      case '1': {
        conv = new MuteConverter;
        stream = conv->work(stream, current_oper);
        break;
      }

      case '2': {
        conv = new MixConverter;
        current_oper.mix_file = argv[current_oper.input_number + 2];
        stream = conv->work(stream, current_oper);
        break;
      }

      case '3': {
        conv = new ReverseConverter;
        current_oper.length = input.len();
        stream = conv->work(stream, current_oper);
        break;
      }
    }
  }

  output.write_to_file(argv[2], input.header(), input.data(), stream);

  return 0;
}