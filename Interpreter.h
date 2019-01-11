#ifndef SEMESTERPROJECT1TRY2_INTERPRETER_H
#define SEMESTERPROJECT1TRY2_INTERPRETER_H
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "Maps.h"
#include "Boolean.h"
#include "Command.h"
#include "Commands.h"
using namespace std;

class Interpreter {

public:

    void closeConnections();
    vector<string> lexer(string fileName);
    void parser(vector<string> comm);
    vector<string> splitBySpace(string toSeprite);
    bool lookForExpression(string toChack);
    void fixExpressions(string &toFix); // rplace the exprssion with double string
    bool onlyNum(string &toChack);
    vector<string> copeWhileIf(vector<string> &comm, int &i);

};


#endif //SEMESTERPROJECT1TRY2_INTERPRETER_H
