#include "LZWcompressor.h"
#include "filehandler.h"
#include <cassert>
#include <iostream>
#include <filesystem>

int test_lzw() {
    string inputFile  = "data/test/lzw_sample.txt";
    string compressed = "data/test/lzw_sample.lzw";
    string outputFile = "data/test/lzw_output.txt";

    // string inputFile  = "data/test/lzw_snail.bmp";
    // string compressed = "data/test/lzw_snail.lzw";
    // string outputFile = "data/test/lzw_snail_output.bmp";

    LZWCompressor lzw;

    lzw.compress(inputFile, compressed);
    lzw.decompress(compressed, outputFile);

    auto original = FileHandler::readFile(inputFile);
    auto decompressed = FileHandler::readFile(outputFile);

    assert(original == decompressed);

    cout << "LZW test passed: decompressed file matches original." << endl;

    auto inputSize = filesystem::file_size(inputFile);
    auto compressedSize = filesystem::file_size(compressed);

    cout << "Original size:   " << inputSize << " bytes\n";
    cout << "Compressed size: " << compressedSize << " bytes\n";

    if (compressedSize < inputSize) {
        cout << "Size Reduction Check: PASS" << endl;
    } else {
        cout << "Size Reduction Check: FAIL" << endl;
    }
    return 0;
}