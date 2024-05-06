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
        while (!line.empty() && line[0] == ' ') {
            line.erase(0, 1);
        }

        if (line.empty()) {
            continue;
        }

        if (line.find("//") != std::string::npos && line.find("//") == 0) {
            continue;
        }
        
        int index = 1;
        while (index < line.length() && line[index] != '\n') {
            if (isspace(line[index-1]) && isspace(line[index])) {
                line.erase(index-1, 1);
            } else {
                index++;
            }
        }

        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Comment lines removed successfully." << std::endl;
    return 0;
}
