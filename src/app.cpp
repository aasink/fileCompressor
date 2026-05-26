#include "app.h"
#include "filehandler.h"
#include <iostream>
using namespace std;

App::App(const string& option, const string& inputFile, const string& outputFile, const string& algorithm)
    : option(option), inputFile(inputFile), outputFile(outputFile), algorithm(algorithm) {}

void App::run() {
    cout << "Running application..." << endl;
    cout << "Mode: " << option << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Algorithm: " << algorithm << endl;

    if (algorithm == "rle") {
        // RLECompressor compressor;
        // compressor.compress(inputFile, outputFile);
    }
}
