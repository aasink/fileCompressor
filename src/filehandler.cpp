#include "filehandler.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
using namespace std;

vector<char> FileHandler::readBinary(const string& inputFile) {
    ifstream in (inputFile, ios::binary);
    if (!in) {
         ("Failed to open file for reading: " + inputFile);
    }

}
    