#include <fstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <vector>
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



int main() {
  
    stack<char> compiler;
    string inputs[3] = {"(i+i)*i$", "i*(i-i)$", "i(i+i)$"};

    int twodarray[5][8] = 
    {
       //i,+,-,*,/,(,),$
        {1,0,0,0,0,1,0,0}, //E
        {0,2,3,0,0,0,4,4}, //Q
        {5,0,0,0,0,5,0,0}, //T
        {0,4,4,6,7,0,4,4}, //R
        {8,0,0,0,0,9,0,0}  //F
    };
 // 0: reject, 1: TQ, 2: +TQ, 3: -TQ, 4: lambda, 5: FR, 6: *FR, 7: /FR, 8: i, 9: (E)

    char key[][3] = {
        {'Q','T'},
        {'Q', 'T', '+'},
        {'Q', 'T', '-'},
        {'l'}, //lambda
        {'R', 'F'},
        {'R','F','*'},
        {'R','F','/'},
        {'i'},
        {')', 'E', '('}
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
