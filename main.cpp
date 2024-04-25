#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("finalv1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::ofstream outputFile("final24.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        inputFile.close();
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        while (line.find(" ") == 0){
            
        }
        if (line.find("//") != std::string::npos && line.find("//") == 0) {
            continue;
        }
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Comment lines removed successfully." << std::endl;
    return 0;
}
