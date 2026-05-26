#include "RLEcompressor.h"
#include "filehandler.h"
#include <cassert>
#include <iostream>
#include <filesystem>

int test_rle() {
    string inputFile  = "data/test/sample.txt";
    string compressed = "data/test/sample.rle";
    string outputFile = "data/test/output.txt";

    RLECompressor rle;

    rle.compress(inputFile, compressed);
    rle.decompress(compressed, outputFile);

    auto original   = FileHandler::readFile(inputFile);
    auto decompressed = FileHandler::readFile(outputFile);

    assert(original == decompressed);

    cout << "RLE test passed: decompressed file matches original." << endl;

    auto inputSize      = filesystem::file_size(inputFile);
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
