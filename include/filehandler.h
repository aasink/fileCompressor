#pragma once
#include <string>
#include <vector>
using namespace std;

#pragma pack(push, 1)
struct FileHeader {
    char extension[8];           // file extension of input file 
    uint8_t algorithm;          // 1=RLE, 2=Huffman, 3=LZW
};
#pragma pack(pop)

class FileHandler {
public:
    static vector<unsigned char> readFile(const string& inputFile);

    static pair<FileHeader, vector<unsigned char>> readFileWithHeader(const string& inputFile);

    static void writeFile(const string& outputFile, const vector<unsigned char>& data);

    static void writeFile(const string& outputFile, const vector<unsigned char>& data, const FileHeader& header);

    static string getDefaultOutputName(const string& inputFile, const string& algorithm, const string& option);

    static string resolveOutputPath(const string& inputFile, const string& outputFile, const string& algorithm, const string& option);

    static string updateExtension(const char* extension, const string& outPath);

    static FileHeader makeHeader(const string& ext, uint8_t algo);

    static FileHeader readHeader(ifstream& in);

};
