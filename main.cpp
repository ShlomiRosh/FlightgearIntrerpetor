#include <iostream>
#include <stack>
#include <vector>
#include "Interpreter.h"

using namespace std;
int main(int argc, char *argv[]) {

    string fileName = argv[1];
    Interpreter interpreter;
    vector<string> linesOfFile = interpreter.lexer(fileName);
    interpreter.parser(linesOfFile);
    interpreter.closeConnections();

    return 0;
}
