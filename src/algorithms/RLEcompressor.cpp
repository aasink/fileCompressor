#include "RLEcompressor.h"
#include "filehandler.h"
#include <iostream>

void RLECompressor::compress(const string& inputFile, const string& outputFile) {
    auto data = FileHandler::readFile(inputFile);
    auto compressed = runLengthEncode(data);

    string outPath = FileHandler::resolveOutputPath(inputFile, outputFile, "rle", "compress");
    FileHandler::writeFile(outPath, compressed);

    cout << "Compressed to: " << outPath << "\n" << endl;
}

void RLECompressor::decompress(const string& inputFile, const string& outputFile) {
    auto data = FileHandler::readFile(inputFile);
    auto decompressed = runLengthDecode(data);

    string outPath = FileHandler::resolveOutputPath(inputFile, outputFile, "rle", "decompress");
    FileHandler::writeFile(outPath, decompressed);

    cout << "Decompressed to: " << outPath << "\n" << endl;
}

vector<char> RLECompressor::runLengthEncode(const vector<char>& data) {
    vector<char> result;
    for (size_t i = 0; i < data.size();) {
        char current = data[i];
        size_t count = 1;
        while (i + count < data.size() && data[i + count] == current) {
            ++count;
        }
        result.push_back(current);
        result.push_back(static_cast<char>(count));
        i += count;
    }
    return result;
}

vector<char> RLECompressor::runLengthDecode(const vector<char>& data) {
    vector<char> result;
    for (size_t i = 0; i + 1 < data.size(); i += 2) {
        char value = data[i];
        unsigned char count = static_cast<unsigned char>(data[i + 1]);
        result.insert(result.end(), count, value);
    }
    return result;
}
