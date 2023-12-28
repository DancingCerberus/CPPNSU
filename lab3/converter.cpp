#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
//#include "converter.h"

std::stringstream MuteConverter::work(std::stringstream &stream, operation oper) {
    std::stringstream res;
//    std::cout << oper.start << "  " << oper.finish << std::endl;
    int seconds = 0, samples = 0;
    long long sample;
    stream.read(reinterpret_cast<char*>(&sample), 2);

    if (oper.start == 0) {
        res.write(reinterpret_cast<char*>(&sample), 2);
    }

    while (!stream.eof()) {
        if ((seconds >= oper.start && seconds < oper.finish) || (oper.finish == 0 && oper.start == 0)) {
            sample = 0;
            res.write(reinterpret_cast<char*>(&sample), 2);
        } else {
            res.write(reinterpret_cast<char*>(&sample), 2);
        }

        stream.read(reinterpret_cast<char*>(&sample), 2);
        samples++;
        if (samples == oper.sampleRate) {
            seconds++;
            samples = 0;
        }
    }

    stream.clear();
    return res;
}


std::stringstream MixConverter::work(std::stringstream &stream, operation oper) {
    std::stringstream res;
    std::ifstream mix_stream(oper.mix_file, std::ios::binary);

    int seconds = 0, samples = 0;
    long long original_sample, mix_sample;
    stream.read(reinterpret_cast<char*>(&original_sample), 2);
    mix_stream.read(reinterpret_cast<char*>(&mix_sample), 2);

    while (!stream.eof()) {
        if ((seconds >= oper.start && seconds < oper.finish) || (oper.finish == 0 && seconds >= oper.start)) {
            if (!mix_stream.eof()) {
                original_sample = (original_sample + mix_sample) / 2;
            }
            res.write(reinterpret_cast<char*>(&original_sample), 2);
        } else {
            res.write(reinterpret_cast<char*>(&original_sample), 2);
        }

        stream.read(reinterpret_cast<char*>(&original_sample), 2);
        mix_stream.read(reinterpret_cast<char*>(&mix_sample), 2);
        samples++;
        if (samples % oper.sampleRate == 0) {
            seconds++;
            samples = 0;
        }
    }

    mix_stream.close();
    stream.clear();
    return res;
}


std::stringstream ReverseConverter::work(std::stringstream &stream, operation oper) {
    std::stringstream res;

    int seconds = 0, samples = 0;
    long long sample;
    long long after_reverse = oper.sampleRate * 2 * oper.finish;
    long long reverse_cursor = after_reverse;

    if (oper.start == 0 && oper.finish == 0) {
        stream.read(reinterpret_cast<char*>(&sample), 2);
        res.write(reinterpret_cast<char*>(&sample), 2);
        reverse_cursor = oper.length - 2;
        while (reverse_cursor > 0) {
            stream.seekg(reverse_cursor);
            reverse_cursor -= 2;
            stream.read(reinterpret_cast<char*>(&sample), 2);
            res.write(reinterpret_cast<char*>(&sample), 2);
        }

        return res;
    }

    stream.read(reinterpret_cast<char*>(&sample), 2);
    while (!stream.eof()) {
        if ((seconds >= oper.start && seconds < oper.finish)) {
            stream.seekg(reverse_cursor);
            reverse_cursor -= 2;
            stream.read(reinterpret_cast<char*>(&sample), 2);
            res.write(reinterpret_cast<char*>(&sample), 2);
        }
        else {
            res.write(reinterpret_cast<char*>(&sample), 2);
            stream.read(reinterpret_cast<char*>(&sample), 2);
        }

        samples++;

        if (samples == oper.sampleRate) {
            seconds++;
            samples = 0;
        }

        if (seconds >= oper.finish && reverse_cursor != -256) {
            stream.seekg(oper.sampleRate * 2 * oper.finish);
            reverse_cursor = -256;
        }
    }

    stream.clear();
    return res;
}
