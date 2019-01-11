#include <sstream>
#include "Interpreter.h"
#include "ShuntingYardD.h"

vector<string> Interpreter::lexer(const string fileName) {
    vector<string> lines;
    fstream readFile;
    string readLine;
    readFile.open(fileName, ios_base::in);
    if (!readFile.is_open()) {
        throw "problem oppening file";
    }
    while (!readFile.eof()) {
        getline(readFile, readLine);
        lines.push_back(readLine);
    }
    readFile.close();
    return lines;
}

void Interpreter::parser(vector<string> comm) {
    for (int i = 0; i < comm.size(); i++) {
        vector<string> toInsert = splitBySpace(comm[i]);
        if (toInsert.empty()) {
            continue;
        }
        if (toInsert[0] == "openDataServer") {
            if (lookForExpression(toInsert[1])) {
                fixExpressions(toInsert[1]);
            }
            if (lookForExpression(toInsert[2])) {
                fixExpressions(toInsert[2]);
            }
            OpenDateServerCommand openDateServerCommand;
            openDateServerCommand.doCommand(toInsert, comm[i]);
        } else if (toInsert[0] == "connect") {
            if (lookForExpression(toInsert[2])) {
                fixExpressions(toInsert[2]);
            }
            ConnectCommand connectCommand;
            connectCommand.doCommand(toInsert, comm[i]);
        } else if (toInsert[0] == "var" && toInsert[3] == "bind") { // fix bind
            BindCommand bindCommand;
            bindCommand.doCommand(toInsert, comm[i]);
        } else if ((toInsert[0] == "var" && onlyNum(toInsert[3])) ||
                (toInsert[0] == "var" && Maps::getSymbolTable().count(toInsert[3])) ||
                (Maps::getSymbolTable().count(toInsert[0]) && Maps::getSymbolTable().count(toInsert[2])
                 && toInsert.size() == 3) ||
                (Maps::getSymbolTable().count(toInsert[0]) && onlyNum(toInsert[2]) && toInsert.size() <= 3) ||
                ((toInsert[0] == "var" || Maps::getSymbolTable().count(toInsert[0]))
                 && lookForExpression(comm[i]))) {
            /*
             * the List of cases in next order
             * new Var = number
             * new Var = exsit var
             * exsit var = exist var
             * exsit var = number
             * new/exsit var = Expression
             */
            VarCommand varCommand;
            varCommand.doCommand(toInsert, comm[i]);
        } else if (toInsert[0] == "while" || toInsert[0] == "if") {
            vector<string> conditions = copeWhileIf(comm, i);
            if (toInsert[0] == "while") {
                Boolean boolean(toInsert[1], toInsert[2], toInsert[3]);
                while (boolean.calculate()) {
                    parser(conditions);
                }
            } else if (toInsert[0] == "if") {
                Boolean boolean(toInsert[1], toInsert[2], toInsert[3]);
                if (boolean.calculate()) {
                    parser(conditions);
                }
            }
        } else if (toInsert[0] == "sleep") {
            if (lookForExpression(toInsert[1])) {
                fixExpressions(toInsert[1]);
            }
            SleepCommand sleepCommand;
            sleepCommand.doCommand(toInsert, comm[i]);
        } else if (toInsert[0] == "print") {
            PrintCommand printCommand1;
            printCommand1.doCommand(toInsert, comm[i]);
        }
    }
}

vector<string> Interpreter::splitBySpace(string toSeprite) {
    istringstream s2(toSeprite);
    vector<string> newV;
    string tmp;
    while (s2 >> tmp) {
        newV.push_back(tmp);
    }
    return newV;
}

bool Interpreter::lookForExpression(string toChack) {
    for (char i : toChack) {
        if (i == '+' || i == '-' || i == '*' || i == '/') {
            return true;
        }
    }
    return false;
}

void Interpreter::fixExpressions(string &toFix) {
    ShuntingYardD yardD;
    int correctNum = static_cast<int>(yardD.infixToPrefix(toFix));
    toFix = to_string(correctNum);
}

bool Interpreter::onlyNum(string &toChack) {
    for (int j = 0; j < toChack.size(); j++) {
        if (toChack[0] != '-' && (!isdigit(toChack[j]) && toChack[j] != '.')) {
            return false;
        }
    }
    return true;
}

vector<string> Interpreter::copeWhileIf(vector<string> &comm, int &i) {
    vector<string> conditions;
    //conditions.push_back(comm[i]);
    int flag = 0;
    if (comm[i].find('{') || comm[i + 1].find('{')) {
        i++;
        flag++;
    }
    while (flag != 0) {
        conditions.push_back(comm[i++]);
        if (comm[i].find('{') != string::npos) {
            flag++;
        }
        if (comm[i].find('}') != string::npos) {
            flag--;
        }
    }
    return conditions;
}

void Interpreter::closeConnections() {
    OpenDateServerCommand::toConnect = true;
    ConnectCommand::stopToConnect();
}
