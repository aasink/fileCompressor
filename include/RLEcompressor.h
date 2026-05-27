#pragma once
#include "compressor.h"
#include <string>
#include <vector>
using namespace std;

class RLECompressor : public Compressor {
public:
    void compress(const string& inputFile, const string& outputFile) override;
    void decompress(const string& inputFile, const string& outputFile) override;

private:
    vector<unsigned char> runLengthEncode(const vector<unsigned char>& data);
    vector<unsigned char> runLengthDecode(const vector<unsigned char>& data);
};
