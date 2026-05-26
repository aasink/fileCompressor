#pragma once
#include <string>
#include <vector>
using namespace std;

class FileHandler {
public:
    static vector<char> readBinary(const string& inputFile);

    static void writeBinary(const string& outputFile, const vector<char>& data);

    static string getDefaultOutputName(const string& inputFile, const string& algorithm, const string& option);

    static string resolveOutputPath(const string& inputFile, const string& outputFile);
};
