#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "wav_file.h"

std::stringstream WAV_file::read_from_file(char* input_file) {
    std::ifstream input(input_file, std::ios::binary);

    if (!input.is_open()) {
        throw "open_error";
    }

    input.read(reinterpret_cast<char*>(&header_), sizeof(wav_hdr));
    data_ = new char[header_.subchunk2Size + 6];
    input.read(data_, header_.subchunk2Size + 6);

    long long sample;
    std::stringstream res;
    input.read(reinterpret_cast<char*>(&sample), 2);
    while (!input.eof()) {
        length_ += 2;
        res.write(reinterpret_cast<char*>(&sample), 2);
        input.read(reinterpret_cast<char*>(&sample), 2);
    }

    input.close();
    return res;
}

void WAV_file::write_to_file(char* output_file, wav_hdr header, char* data, std::stringstream &res) {
    std::ofstream output(output_file, std::ios::binary);

    if (!output.is_open()) {
        throw "open_error";
    }

    output.write(reinterpret_cast<char*>(&header), sizeof(wav_hdr));
    output.write(data, header.subchunk2Size + 6);

    long long sample;
    res.read(reinterpret_cast<char*>(&sample), 2);
    while (!res.eof()) {
        output.write(reinterpret_cast<char*>(&sample), 2);
        res.read(reinterpret_cast<char*>(&sample), 2);
    }

    output.close();
    res.clear();
}

int WAV_file::len() {
    return length_;
}

char* WAV_file::data() {
    return data_;
}

wav_hdr WAV_file::header() {
    return header_;
}