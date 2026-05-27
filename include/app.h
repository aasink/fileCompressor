#pragma once
#include <string>
#include <unordered_set>
using namespace std;


class App {
public:
    App(const string& option, const string& inputFile, const string& outputFile, const string& algorithm);

    void run();

    // supported algorithms
    static const unordered_set<string>& supportedAlgorithms() {
        static const unordered_set<string> algos = {"rle", "huffman", "lzw"};
        return algos;
    }

private:
    string option;
    string inputFile;
    string outputFile;
    string algorithm;
};
