#include "LZWcompressor.h"
#include "filehandler.h"
#include <iostream>
#include <stdexcept>
using namespace std;

vector<unsigned char> LZWCompressor::runLZWEncode(const vector<unsigned char>& data) {
    if (data.empty()) return {};

    unordered_map<string, uint16_t> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[string(1, static_cast<char>(i))] = i;
    }
    uint16_t nextCode = 256;

    vector<unsigned char> result;
    string current = string(1, static_cast<char>(data[0]));

    for (size_t i = 1; i < data.size(); ++i) {
        string next = current + static_cast<char>(data[i]);

        if (dictionary.count(next)) {
            current = next;
        } else {
            uint16_t code = dictionary[current];
            result.push_back(code >> 8);
            result.push_back(code & 0xFF);

            if (nextCode < 65535) {
                dictionary[next] = nextCode++;
            }

            current = string(1, static_cast<char>(data[i]));
        }
    }

    // flush last code
    uint16_t code = dictionary[current];
    result.push_back(code >> 8);
    result.push_back(code & 0xFF);

    return result;
}

vector<unsigned char> LZWCompressor::runLZWDecode(const vector<unsigned char>& data) {
    if (data.empty()) return {};
    if (data.size() % 2 != 0) throw runtime_error("[ERROR] Corrupt LZW data — odd byte count");

    unordered_map<uint16_t, string> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = string(1, static_cast<char>(i));
    }
    uint16_t nextCode = 256;

    uint16_t prevCode = (data[0] << 8) | data[1];
    string prevEntry = dictionary[prevCode];

    vector<unsigned char> result;
    for (unsigned char b : prevEntry) result.push_back(b);

    for (size_t i = 2; i < data.size(); i += 2) {
        uint16_t code = (data[i] << 8) | data[i + 1];

        string entry;
        if (dictionary.count(code)) {
            entry = dictionary[code];
        } else if (code == nextCode) {
            entry = prevEntry + static_cast<char>(prevEntry[0]);
        } else {
            throw runtime_error("[ERROR] Corrupt LZW data — unknown code");
        }

        for (unsigned char b : entry) result.push_back(b);

        if (nextCode < 65535) {
            dictionary[nextCode++] = prevEntry + static_cast<char>(entry[0]);
        }

        prevEntry = entry;
    }

    return result;
}

void LZWCompressor::compress(const string& inputFile, const string& outPath) {
    auto data = FileHandler::readFile(inputFile);
    auto compressed = runLZWEncode(data);

    FileHeader header{};
    string ext = inputFile.substr(inputFile.find_last_of('.') + 1);
    header = FileHandler::makeHeader(ext, 3);  // 3 for LZW

    FileHandler::writeFile(outPath, compressed, header);
    cout << "Compressed to: " << outPath << "\n";
}

void LZWCompressor::decompress(const string& inputFile, const string& outPath) {
    auto [header, data] = FileHandler::readFileWithHeader(inputFile);
    if (header.algorithm != 3) throw runtime_error("[ERROR] Wrong algorithm for this file");

    string newOutPath = FileHandler::updateExtension(header.extension, outPath);
    auto decompressed = runLZWDecode(data);

    FileHandler::writeFile(newOutPath, decompressed);
    cout << "Decompressed to: " << newOutPath << "\n";
}