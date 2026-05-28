#pragma once
#include "compressor.h"
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class LZWCompressor {
public:
    void compress(const string& inputFile, const string& outPath);
    void decompress(const string& inputFile, const string& outPath);

private:
    vector<unsigned char> runLZWEncode(const vector<unsigned char>& data);
    vector<unsigned char> runLZWDecode(const vector<unsigned char>& data);
};