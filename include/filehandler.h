#pragma once
#include <string>
#include <vector>
using namespace std;

class FileHandler {
public:
    static vector<char> readFile(const string& inputFile);

    static void writeFile(const string& outputFile, const vector<char>& data);

    static string getDefaultOutputName(const string& inputFile, const string& algorithm, const string& option);

    static string resolveOutputPath(const string& inputFile, const string& outputFile, const string& algorithm, const string& option);
};
