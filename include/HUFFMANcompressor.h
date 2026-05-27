#pragma once
#include "compressor.h"
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct HuffmanNode {
    unsigned char byte;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(unsigned char b, int f) : byte(b), frequency(f), left(nullptr), right(nullptr) {}
};

struct HuffmanCompare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCompressor: public Compressor {
public:
    void compress(const string& inputFile, const string& outPath);
    void decompress(const string& inputFile, const string& outPath);

private:
    HuffmanNode* buildTree(const unordered_map<unsigned char, int>& freqTable);
    void buildCodes(HuffmanNode* node, const string& code, unordered_map<unsigned char, string>& codes);
    void serializeTree(HuffmanNode* node, vector<unsigned char>& out);
    HuffmanNode* deserializeTree(const vector<unsigned char>& data, size_t& index);
    void deleteTree(HuffmanNode* node);

    vector<unsigned char> runHuffmanEncode(const vector<unsigned char>& data);
    vector<unsigned char> runHuffmanDecode(const vector<unsigned char>& data);
};