#include "filehandler.h"
#include "compressor.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <iostream>
using namespace std;

vector<unsigned char> FileHandler::readFile(const string& inputFile) {
    ifstream in (inputFile, ios::binary);
    if (!in) throw runtime_error("Cannot open file: " + inputFile);

    return vector<unsigned char>((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
}

pair<FileHeader, vector<unsigned char>> FileHandler::readFileWithHeader(const string& inputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) throw runtime_error("Cannot open file: " + inputFile);

    FileHeader header = readHeader(in);

    vector<unsigned char> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    return {header, data};
}

void FileHandler::writeFile(const std::string& outputFile, const std::vector<unsigned char>& data) {
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write to file: " + outputFile);

    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void FileHandler::writeFile(const string& outputFile, const vector<unsigned char>& data, const FileHeader& header) {
    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Cannot write to file: " + outputFile);

    out.write(reinterpret_cast<const char*>(&header), sizeof(header));
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}

string FileHandler::getDefaultOutputName(const string& inputFile, const string& algorithm, const string& option) {

    filesystem::path inputPath(inputFile);
    string base = inputPath.stem().string();

    string extension;
    if (option == "compress") {                             // compression
        if (algorithm == "rle") extension = ".rle";
        else if (algorithm == "huffman") extension = ".huff";
        else if (algorithm == "lzw") extension = ".lzw";
        else extension = ".bin";                            // fallback
    } else {                                                   // decompression
        extension = "_decompressed.txt";
    }

    return (inputPath.parent_path() / (base + extension)).string();
}

string FileHandler::resolveOutputPath(const string& inputFile, const string& outputFile, const string& algorithm, const string& option) {
    string outputPath = outputFile.empty() ? getDefaultOutputName(inputFile, algorithm, option) : outputFile;

    return outputPath;
}

string FileHandler::updateExtension(const char* extension, const string& outPath) {
    filesystem::path path(outPath);
    return (path.parent_path() / (path.stem().string() + "." + extension)).string();
}

FileHeader FileHandler::makeHeader(const string& ext, uint8_t algo) {
    FileHeader header{};
    strncpy(header.extension, ext.c_str(), sizeof(header.extension));
    header.algorithm = algo;
    return header;
}

FileHeader FileHandler::readHeader(ifstream& in) {
    FileHeader header{};
    in.read(reinterpret_cast<char*>(&header), sizeof(header));
    return header;
}
