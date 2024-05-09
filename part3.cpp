#include <fstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

int main()
{
    std::ifstream inputFile("final24.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open input file" << std::endl;
        return 1;
    }

    std::ofstream outfile("output.cpp"); 
    if (!outfile.is_open())
    {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    outfile << "#include <iostream>" << std::endl;
    outfile << "using namespace std;" << std::endl;
    outfile << "int main() {" << std::endl;

    bool definingVariables = false;
    vector<string> placeholder = {};

    std::string line;
    while (std::getline(inputFile, line))
    {

        if (line.substr(0, 7) == "program")
        {
            continue; // Skip to the next line
        }

        else if (line.substr(0, 5) == "begin")
        {
            continue; // Skip to the next line
        }

        else if (line.substr(0, 3) == "end")
        {
            continue; // Skip to the next line
        }

        else if (line.substr(0, 5) == "write")
        {
            int space = line.find(' ', 2);
            int comma = line.find(',');
            if (comma == std::string::npos) {
                outfile << "    std::cout << " << line.substr(space+2, 3) << ";" << std::endl;
            } else {
                outfile << "    std::cout << \"" << line.substr(space+6, 6) << "\"<< " << line.substr(comma+2,2) << ";" << std::endl;
            }

            
        }
        else if (line.substr(0, 3) == "var")
        {
            definingVariables = true;
        }
        else if (definingVariables)
        {
            int colon = line.find(':');

            std::string substringAfterColon = line.substr(colon + 1);

            int nextSpacePos = substringAfterColon.find(' ', 2);

            std::string wordAfterColon = substringAfterColon.substr(0, nextSpacePos);

            outfile << "   " << wordAfterColon.substr(0, 4) << " " << line.substr(0, colon) << ";" << endl;
           
            definingVariables = false;
        }
        else
        {
            outfile << "    " << line << std::endl;
        }
    }

    // Write the end of main function and return statement to the output file
    outfile << "    return 0;" << std::endl;
    outfile << "}" << std::endl;

    // Close the files
    inputFile.close();
    outfile.close();

    std::cout << "C++ source file generated successfully" << std::endl;

    // Compile the generated C++ source file
    std::string compile_command = "clang++ -o output output.cpp";
    int compile_result = system(compile_command.c_str());
    if (compile_result != 0) {
        std::cerr << "Compilation failed!" << std::endl;
        return 1;
    }

    // Run the compiled executable
    std::string run_command = "./output";
    int run_result = system(run_command.c_str());
    if (run_result != 0) {
        std::cerr << "Execution failed!" << std::endl;
        return 1;
    }

    return 0;
}
