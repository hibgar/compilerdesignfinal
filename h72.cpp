#include <fstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

unordered_map<char, int> indexMap = {
    {'i', 0},
    {'+', 1},
    {'-', 2},
    {'*', 3},
    {'/', 4},
    {'(', 5},
    {')', 6},
    {'$', 7}
};

void displayStack(stack<char> stack) {
    vector<char> tempVector;

    // Copy elements from stack to tempVector
    while (!stack.empty()) {
        tempVector.push_back(stack.top());
        stack.pop();
    }

    // Display elements from tempVector
    cout << endl;
    for (auto it = tempVector.rbegin(); it != tempVector.rend(); ++it) {
        cout << *it;
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

    std::ifstream inputFile("finalv24.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Tokenize each line
        std::vector<std::string> tokens = tokenize(line);
        // Output each token
        for (const auto& token : tokens) {
            std::cout << token << std::endl;
        }
    }
  
    stack<char> compiler;
    string inputs[3] = {"(i+i)*i$", "i*(i-i)$", "i(i+i)$"};

    int twodarray[22][33] = 
    {
       //0,1,2,3,4,5,6,7,8,9,p,q,r,s,+,-,*,/,=,l,program,var , ; : ( ) $ begin end. integer write "value=",
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, //P
        {0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //I
        {3,3,3,3,3,3,3,3,3,3,2,2,2,2,4,4,4,4,0,0,0,0,4,4,4,0,4,0,0,0,0,0,0}, //PI
        {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //DL
        {0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //D
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,4,0,0,0,0,0,0,0,0}, //PD
        {}, //T
    };
 // 0: reject, 1: TQ, 2: +TQ, 3: -TQ, 4: lambda, 5: FR, 6: *FR, 7: /FR, 8: i, 9: (E)


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


    string input1 = inputs[2];
    cout <<input1 << endl;
    compiler.push('$');
    compiler.push('E');
    
    int inputNum = 0;
    char currentRead;
    

    while (!compiler.empty()) {
        
        //pop
        char val = compiler.top();
        compiler.pop();

        //read string val
        currentRead = input1[inputNum];
        
        //while no match
        while (val != currentRead) {
            // go to [_,_] -- determine array value based on val
            
            int arrayValue;
            switch (val) {
                case 'E':
                    arrayValue = twodarray[0][indexMap[currentRead]];
                    break;
                case 'Q':
                    arrayValue = twodarray[1][indexMap[currentRead]];
                    break;
                case 'T':
                    arrayValue = twodarray[2][indexMap[currentRead]];
                    break;
                case 'R':
                    arrayValue = twodarray[3][indexMap[currentRead]];
                    break;
                case 'F':
                    arrayValue = twodarray[4][indexMap[currentRead]];
                    break;
            }

            if (arrayValue == 0) {
                cout << endl <<"rejected" << endl;
                return 0;
            }

            // push elements from key[arrayValue] into compiler
            for (size_t i = 0; i < (sizeof(key[arrayValue-1]) / sizeof(key[arrayValue-1][0])); ++i) {
                compiler.push(key[arrayValue-1][i]);
            }
            displayStack(compiler);
            
            
            while ( compiler.top() == 0 or compiler.top() == 'l') {
                compiler.pop();
            }
            val = compiler.top();
            compiler.pop();

            
        }

        displayStack(compiler);

        inputNum++;
        currentRead = input1[inputNum];
        
    }

    cout << endl << "accepted"<< endl;

  return 0;
}
