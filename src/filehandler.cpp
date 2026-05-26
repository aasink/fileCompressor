#include "filehandler.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
using namespace std;

vector<char> FileHandler::readFile(const string& inputFile) {
    ifstream in (inputFile, ios::binary);
    if (!in) throw runtime_error("Cannot open file: " + inputFile);

    return vector<char>((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
}

void FileHandler::writeFile(const string& outputFile, const vector<char>& data) {
    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Cannot write to file: " + outputFile);

    out.write(data.data(), data.size());
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