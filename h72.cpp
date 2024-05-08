#include <fstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

void displayStack(stack<string> stack) {
    vector<string> tempVector;

    // Copy elements from stack to tempVector
    while (!stack.empty()) {
        tempVector.push_back(stack.top());
        stack.pop();
    }

    // Display elements from tempVector
    std::cout << endl;
    for (auto it = tempVector.rbegin(); it != tempVector.rend(); ++it) {
        std::cout << *it << " ";
    }

    // Restore elements to the original stack
    for (auto it = tempVector.rbegin(); it != tempVector.rend(); ++it) {
        stack.push(*it);
    }
}

std::vector<std::string> tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


int main() {

    std::ifstream inputFile("final24.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::vector<std::string> keys = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "p", "q", "r", "s", "+", "-", "*", "/", "=", "l", "program", "var", ";", ":", "(", ")", "$", "begin", "end", "integer", "write", "\"value=\""};
    std::unordered_map<std::string, int> indexMap;

    // Populate the map
    for (int i = 0; i < keys.size(); ++i) {
        indexMap[keys[i]] = i;
    }

    int twodarray[23][33] = 
    {
       //0,1,2,3,4,5,6,7,8,9,p,q,r,s,+,-,*,/,=,l,program,var , ; : ( ) $ begin end. integer write "value=",
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, //P
        {0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //I
        {3,3,3,3,3,3,3,3,3,3,2,2,2,2,4,4,4,4,0,0,0,0,4,4,4,0,4,0,0,0,0,0,0}, //PI
        {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //DL
        {0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //D
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,4,0,0,0,0,0,0,0,0}, //PD
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0}, //T
        {0,0,0,0,0,0,0,0,0,0,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0}, //SL
        {0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,10,0}, //PS
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,11,11,11,0,0,0,0,0,0,0,0,0,0,0,0,12,0}, //S
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0}, //W
        {0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14}, //R
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,15,0,0,0,0,0,0,0,0,0,0,0,0}, //A
        {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0}, //E
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,18,0,0,0,0,0,0,0,4,0,0,4,0,0,0,0,0,0}, //PE
        {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,0,0,0,0,0,0,0,0,0,19,0,0,0,0,0,0,0}, //M
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,20,21,0,0,0,0,0,4,0,0,4,0,0,0,0,0,0}, //PM
        {22,22,22,22,22,22,22,22,22,22,22,22,22,22,23,23,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0}, //F
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,25,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0}, // N
        {26,26,26,26,26,26,26,26,26,26,0,0,0,0,4,4,4,4,0,0,0,0,0,4,0,0,4,0,0,0,0,0,0}, //PN
        {4,4,4,4,4,4,4,4,4,4,0,0,0,0,27,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //G
        {29,30,31,32,33,34,35,36,37,38,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //X
        {0,0,0,0,0,0,0,0,0,0,39,40,41,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //L
    };


    vector<vector<string>> key =
    { 
        // 0 for reject
        {"program", "I", ";", "var", "DL", "begin", "SL", "end."}, //1
        {"L", "PI"}, //2
        {"X", "PI"}, //3
        {"l"}, //4
        {"D", ":", "T", ";"}, //5
        {",", "D"}, //6
        {"I", "PD"}, //7
        {"integer"}, //8
        {"S", "PS"}, //9
        {"SL"}, //10
        {"A", "S"}, //11
        {"W"}, //12
        {"write", "(", "R", "I", ")", ";"}, //13
        {"\"value=\","}, //14
        {"I", "=", "E", ";"}, //15
        {"M", "PE"}, //16
        {"+", "M", "PE"}, //17
        {"-", "M", "PE"}, //18
        {"F", "PM"}, //19
        {"*", "F", "PM"}, //20
        {"/", "F", "PM"}, //21
        {"I"}, //22
        {"N"}, //23
        {"(","E",")"}, //24
        {"S", "X", "PN"}, //25
        {"X", "PN"}, //26
        {"+"}, //27
        {"-"}, //28
        {"0"}, //29
        {"1"}, //30
        {"2"}, //31
        {"3"}, //32
        {"4"}, //33
        {"5"}, //34
        {"6"}, //35
        {"7"}, //36
        {"8"}, //37
        {"9"}, //38
        {"p"}, //39
        {"q"}, //40
        {"r"}, //41
        {"s"}, //42
    }; 

    stack<string> compiler;
    compiler.push("$");
    compiler.push("P");
    
    
    string currentRead;
    

    while (!compiler.empty()) {
        
        string val = compiler.top();
        compiler.pop();
        int arrayValue;

        //read token
        std::string line;
        while (std::getline(inputFile, line)) {
            std::vector<std::string> tokens = tokenize(line);
            // for each token
            for (const auto& token : tokens) {
                
                currentRead = token;
                
                //while no match
                while (val != currentRead) {
                    
                    // go to [_,_] -- determine array value based on val
                    if (val == "P") {
                        arrayValue = twodarray[0][indexMap[currentRead]];
                    } else if (val == "I") {
                        arrayValue = twodarray[1][indexMap[std::string(1,currentRead[0])]];    
                    } else if (val == "L") {

                        int index = 0;
                       

                        while (val != currentRead and index < token.size() ) {
                            currentRead = std::string(1,token[index]);
                            if (val == "PI") {
                                compiler.pop();
                                arrayValue = twodarray[2][indexMap[std::string(1,currentRead[index])]];
                            } else {
                                if (isdigit(currentRead[index])) {
                                    arrayValue = twodarray[21][indexMap[std::string(1,currentRead[index])]];
                                }
                                if (isalpha(currentRead[index])){
                                    arrayValue = twodarray[22][indexMap[std::string(1,currentRead[index])]];
                                }
                            }

                            for (int i = key[arrayValue-1].size() - 1; i >= 0; i--) {
                                compiler.push(key[arrayValue-1][i]);
                            }
                            
                            compiler.pop(); 
                            
                            if (isdigit(token[index])) {
                                arrayValue = twodarray[21][indexMap[std::string(1,token[index])]];
                            }
                            if (isalpha(token[index])){
                                arrayValue = twodarray[22][indexMap[std::string(1,token[index])]];
                            }

                            compiler.push(key[arrayValue-1][0]);

                            compiler.pop();

                            val = compiler.top(); // == PI

                            index++;
                        }
                        
                    } else if (val == "PI") {
                        arrayValue = twodarray[2][indexMap[currentRead]];
                    }
                    

                    if (arrayValue == 0) {
                        std::cout << endl << "rejected" << endl;
                        return 0;
                    }

                    // push elements from key[arrayValue] into compiler
                    for (int i = key[arrayValue-1].size() - 1; i >= 0; --i) {
                        compiler.push(key[arrayValue-1][i]);
                    }
                    
                    
                    while ( compiler.top() == "0" or compiler.top() == "l") {
                        compiler.pop();
                    }
                    val = compiler.top();
                    compiler.pop();

                }

                displayStack(compiler);

                val = compiler.top();
                compiler.pop();

            }
        }
    }

    std::cout << endl << "accepted" << endl;

  return 0;
}
