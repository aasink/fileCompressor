#include "HUFFMANcompressor.h"
#include "filehandler.h"
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

HuffmanNode* HuffmanCompressor::buildTree(const unordered_map<unsigned char, int>& freqTable) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanCompare> pq;

    for (const auto& [byte, freq] : freqTable) {
        pq.push(new HuffmanNode(byte, freq));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode(0, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.top();
}

void HuffmanCompressor::buildCodes(HuffmanNode* node, const string& code,
                                    unordered_map<unsigned char, string>& codes) {
    if (!node) return;
    if (!node->left && !node->right) {   // leaf node
        codes[node->byte] = code.empty() ? "0" : code;
        return;
    }
    buildCodes(node->left,  code + "0", codes);
    buildCodes(node->right, code + "1", codes);
}

void HuffmanCompressor::serializeTree(HuffmanNode* node, vector<unsigned char>& out) {
    if (!node) return;
    if (!node->left && !node->right) {   // leaf
        out.push_back(1);                // 1 = leaf marker
        out.push_back(node->byte);
        return;
    }
    out.push_back(0);                    // 0 = internal node marker
    serializeTree(node->left,  out);
    serializeTree(node->right, out);
}

HuffmanNode* HuffmanCompressor::deserializeTree(const vector<unsigned char>& data, size_t& index) {
    if (index >= data.size()) throw runtime_error("[ERROR] Corrupt tree data");

    unsigned char marker = data[index++];
    if (marker == 1) {                   // leaf
        unsigned char byte = data[index++];
        return new HuffmanNode(byte, 0);
    }
    HuffmanNode* node = new HuffmanNode(0, 0);
    node->left  = deserializeTree(data, index);
    node->right = deserializeTree(data, index);
    return node;
}

void HuffmanCompressor::deleteTree(HuffmanNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

vector<unsigned char> HuffmanCompressor::runHuffmanEncode(const vector<unsigned char>& data) {
    if (data.empty()) return {};

    unordered_map<unsigned char, int> freqTable;
    for (unsigned char b : data) freqTable[b]++;

    HuffmanNode* root = buildTree(freqTable);
    unordered_map<unsigned char, string> codes;
    buildCodes(root, "", codes);

    vector<unsigned char> result;
    serializeTree(root, result);
    deleteTree(root);

    size_t originalSize = data.size();
    for (int i = 7; i >= 0; --i) {
        result.push_back((originalSize >> (i * 8)) & 0xFF);
    }

    unsigned char currentByte = 0;
    int bitCount = 0;
    for (unsigned char b : data) {
        for (char bit : codes[b]) {
            currentByte = (currentByte << 1) | (bit - '0');
            if (++bitCount == 8) {
                result.push_back(currentByte);
                currentByte = 0;
                bitCount = 0;
            }
        }
    }
    if (bitCount > 0) {                  // flush remaining bits
        currentByte <<= (8 - bitCount);
        result.push_back(currentByte);
    }

    return result;
}

vector<unsigned char> HuffmanCompressor::runHuffmanDecode(const vector<unsigned char>& data) {
    if (data.empty()) return {};

    size_t index = 0;

    HuffmanNode* root = deserializeTree(data, index);

    size_t originalSize = 0;
    for (int i = 0; i < 8; ++i) {
        originalSize = (originalSize << 8) | data[index++];
    }

    vector<unsigned char> result;
    HuffmanNode* current = root;
    for (size_t i = index; i < data.size() && result.size() < originalSize; ++i) {
        for (int bit = 7; bit >= 0 && result.size() < originalSize; --bit) {
            bool goRight = (data[i] >> bit) & 1;
            current = goRight ? current->right : current->left;

            if (!current->left && !current->right) {   // leaf reached
                result.push_back(current->byte);
                current = root;
            }
        }
    }

    deleteTree(root);
    return result;
}

void HuffmanCompressor::compress(const string& inputFile, const string& outPath) {
    auto data = FileHandler::readFile(inputFile);
    auto compressed = runHuffmanEncode(data);

    FileHeader header{};
    string ext = inputFile.substr(inputFile.find_last_of('.') + 1);
    header = FileHandler::makeHeader(ext, 2);  // 2 for Huffman

    FileHandler::writeFile(outPath, compressed, header);
    cout << "Compressed to: " << outPath << endl;
}

void HuffmanCompressor::decompress(const string& inputFile, const string& outPath) {
    auto [header, data] = FileHandler::readFileWithHeader(inputFile);
    if (header.algorithm != 2) throw runtime_error("[ERROR] Wrong algorithm for this file");

    string newOutPath = FileHandler::updateExtension(header.extension, outPath);
    auto decompressed = runHuffmanDecode(data);

    FileHandler::writeFile(newOutPath, decompressed);
    cout << "Decompressed to: " << newOutPath << endl;
}