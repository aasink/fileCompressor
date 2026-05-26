#pragma once
#include <string>

class Compressor {
public:
    virtual ~Compressor() = default;

    virtual void compress(const std::string& inputFile, const std::string& outputFile) = 0;

    virtual void decompress(const std::string& inputFile, const std::string& outputFile) = 0;
};
