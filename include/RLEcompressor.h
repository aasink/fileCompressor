#pragma once
#include "compressor.h"
#include <string>
#include <vector>

class RLECompressor : public Compressor {
public:
    void compress(const std::string& inputFile, const std::string& outputFile) override;
    void decompress(const std::string& inputFile, const std::string& outputFile) override;

private:
    std::vector<char> runLengthEncode(const std::vector<char>& data);
    std::vector<char> runLengthDecode(const std::vector<char>& data);
};
