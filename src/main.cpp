#include "app.h"
#include <iostream>
#include <filesystem>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {                     // correct usage
        cerr << "\n[ERROR]: Improper arguments.\n" << " Usage: " << argv[0] << " compress|decompress <input_file> [--output <output_file>] [--algorithm <algorithm>]\n" << endl;
        return 1;
    }

    string option = argv[1];
    string input_file = argv[2];
    string output_file = "";    // default to empty string 
    string algorithm = "rle";   // default to RLE 

    if (option != "compress" && option != "decompress") {
        cerr << "[ERROR]: Invalid option. Use compress or decompress.\n" << endl;
        return 1;           // ensure valid option
    }

    if (!filesystem::exists(input_file)) {
        cerr << "[ERROR]: Input file does not exist.\n" << endl;
        return 1;           // ensure input file exists
    }

    if (argc > 3) {
        for (int i = 3; i < argc; i++) {
            string o_arg = argv[i];
            if (o_arg == "--output" && i + 1 < argc) {      // get specified output name
                output_file = argv[++i];
            } 
            else if (o_arg == "--algorithm" && i + 1 < argc) {      // get specified algorithm
                algorithm = argv[++i];
                if (!App::supportedAlgorithms().count(algorithm)) {     // ensure valid algorithm
                    cerr << "[ERROR]: Unsupported algorithm '" << algorithm << "'.\n" << endl;
                    return 1;
                }
            } 
            else {
                cerr << "[ERROR]: Unknown or incomplete argument: " << o_arg << "\n" << endl;
                return 1;
            }
        }
    }

    //test
    //cout << "Params to Pass:\tOption: " << option << "\tInput File: " << input_file << "\tOutput File: " << output_file << "\tAlgorithm: " << algorithm << endl;

    App app(option, input_file, output_file, algorithm);
    app.run();
    return 0;
}

