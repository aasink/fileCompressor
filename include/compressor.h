#pragma once
#include <string>
#include <fstream>
using namespace std;

class Compressor {
public:
    virtual ~Compressor() = default;

    virtual void compress(const string& inputFile, const string& outputFile) = 0;

    virtual void decompress(const string& inputFile, const string& outputFile) = 0;
};
