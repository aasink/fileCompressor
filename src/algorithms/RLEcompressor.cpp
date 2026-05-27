#include "RLEcompressor.h"
#include "filehandler.h"
#include <iostream>

void RLECompressor::compress(const string& inputFile, const string& outPath) {
    auto data = FileHandler::readFile(inputFile);
    auto compressed = runLengthEncode(data);

    FileHeader header{};
    string ext = inputFile.substr(inputFile.find_last_of('.') + 1);

    header = FileHandler::makeHeader(ext, 1); // 1 for RLE

    FileHandler::writeFile(outPath, compressed, header);

    cout << "Compressed to: " << outPath << "\n" << endl;
}

void RLECompressor::decompress(const string& inputFile, const string& outPath) {
    auto [header, data] = FileHandler::readFileWithHeader(inputFile);
    if (header.algorithm != 1) throw runtime_error("[ERROR]Wrong algorithm for this file");

    string newOutPath = FileHandler::updateExtension(header.extension, outPath);

    auto decompressed = runLengthDecode(data);

    FileHandler::writeFile(newOutPath, decompressed);

    cout << "Decompressed to: " << outPath << "\n" << endl;
}

vector<unsigned char> RLECompressor::runLengthEncode(const vector<unsigned char>& data) {
    vector<unsigned char> compressed;
    for (size_t i = 0; i < data.size();) {     
        unsigned char current = data[i];
        uint8_t count = 1;
        while (i + count < data.size() && data[i + count] == current && count < UINT8_MAX) {
            ++count;
        }
        compressed.push_back(current);
        compressed.push_back(static_cast<unsigned char>(count));
        i += count;
    }

    return compressed;
}

vector<unsigned char> RLECompressor::runLengthDecode(const vector<unsigned char>& data) {
    vector<unsigned char> result;
    for (size_t i = 0; i + 1 < data.size(); i += 2) {
        unsigned char value = data[i];
        unsigned char count = static_cast<unsigned char>(data[i + 1]);
        if (count == 0) continue;
        result.insert(result.end(), count, value);
    }
    return result;
}
