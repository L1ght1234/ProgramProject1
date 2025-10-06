#include <iostream>
#include <string>
#include <stdexcept>
#include "affine.h"
#include "affine_operator.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
            return 1;
        }

        std::string inFile = argv[1];
        std::string outFile = argv[2];

        AffineSystem sys;
        sys.loadFromFile(inFile);

        generateSequenceAndWrite(sys, outFile);

        std::cout << "Done. Generated " << sys.N << " points in file: " << outFile << '\n';
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 2;
    }
}