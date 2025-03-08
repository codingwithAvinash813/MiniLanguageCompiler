#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

// Symbol Table
map<string, int> variables;

// Function to evaluate an expression (supports +, -, *, /)
int evaluate(string expr) {
    stringstream ss(expr);
    int result, num;
    char op;
    ss >> result;
    while (ss >> op >> num) {
        if (op == '+') result += num;
        else if (op == '-') result -= num;
        else if (op == '*') result *= num;
        else if (op == '/') result /= num;
    }
    return result;
}

// Function to execute a single command
void execute(string line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    
    while (ss >> token) tokens.push_back(token);

    if (tokens.size() == 4 && tokens[0] == "let") {
        // Variable assignment: let x = 5;
        string varName = tokens[1];
        int value = evaluate(tokens[3]);
        variables[varName] = value;
    } else if (tokens.size() == 2 && tokens[0] == "print") {
        // Print statement: print x;
        string varName = tokens[1];
        if (variables.find(varName) != variables.end()) {
            cout << variables[varName] << endl;
        } else {
            cout << "Error: Undefined variable " << varName << endl;
        }
    } else if (tokens.size() > 5 && tokens[0] == "if") {
        // Simple if condition: if (x > y) print(x);
        string var1 = tokens[1];
        string op = tokens[2];
        string var2 = tokens[3];
        string command = tokens[5];
        string targetVar = tokens[6];

        if (variables.find(var1) != variables.end() && variables.find(var2) != variables.end()) {
            bool condition = false;
            if (op == ">") condition = variables[var1] > variables[var2];
            else if (op == "<") condition = variables[var1] < variables[var2];
            else if (op == "==") condition = variables[var1] == variables[var2];

            if (condition) execute(command + " " + targetVar);
        } else {
            cout << "Error: Undefined variables in condition" << endl;
        }
    } else {
        cout << "Syntax Error!" << endl;
    }
}

// Main function
int main() {
    cout << "Mini-Language Compiler (Type 'exit' to quit)\n";
    
    string input;
    while (true) {
        cout << ">>> ";
        getline(cin, input);
        if (input == "exit") break;
        execute(input);
    }

    return 0;
}