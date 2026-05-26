#include "app.h"
#include "filehandler.h"
#include "RLEcompressor.h"
#include <iostream>
#include <memory>
using namespace std;

App::App(const string& option, const string& inputFile, const string& outputFile, const string& algorithm)
    : option(option), inputFile(inputFile), outputFile(outputFile), algorithm(algorithm) {}

void App::run() {
    cout << "\nRunning application..." << endl;
    cout << "Mode: " << option << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Algorithm: " << algorithm << endl;

    unique_ptr<Compressor> compressor;   

    if (algorithm == "rle") compressor = make_unique<RLECompressor>();
    else {
        cerr << "[ERROR]: Unsupported algorithm '" << algorithm << "'.\n" << endl;
        return;
    }

    try {
        string outPath = FileHandler::resolveOutputPath(inputFile, outputFile, algorithm, option);

        if (option == "compress") {
            compressor->compress(inputFile, outPath);
        } else if (option == "decompress") {
            compressor->decompress(inputFile, outPath);
        } else {
            cerr << "Unknown option: " << option << endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
