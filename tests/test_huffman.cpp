#include "HUFFMANcompressor.h"
#include "filehandler.h"
#include <cassert>
#include <iostream>
#include <filesystem>

int test_huffman() {
    string inputFile  = "data/test/huffman_sample.txt";
    string compressed = "data/test/huffman_sample.huf";
    string outputFile = "data/test/huffman_output.txt";

    // string inputFile  = "data/test/huffman_snail.bmp";
    // string compressed = "data/test/huffman_snail.huf";
    // string outputFile = "data/test/huffman_snail_output.bmp";

    HuffmanCompressor huffman;

    huffman.compress(inputFile, compressed);
    huffman.decompress(compressed, outputFile);

    auto original = FileHandler::readFile(inputFile);
    auto decompressed = FileHandler::readFile(outputFile);

    assert(original == decompressed);

    cout << "Huffman test passed: decompressed file matches original." << endl;

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