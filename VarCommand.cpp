#include "Commands.h"

void VarCommand::doCommand(vector<string> parameters, string line) {
            /*
             * the List of cases in next order
             * new Var = number
             * new Var = exsit var
             * exsit var = exist var
             * exsit var = number
             * new/exsit var = Expression
             */
    if ((parameters[0] == "var" && onlyNum(parameters[3]))) {
        Maps::setSymbolTable(parameters[1], stod(parameters[3]));
    } else if ((parameters[0] == "var" && Maps::getSymbolTable().count(parameters[3]))) {
        Maps::setSymbolTable(parameters[1], Maps::getSymbolTable().find(parameters[3])->second);
    } else if ((Maps::getSymbolTable().count(parameters[0]) && Maps::getSymbolTable().count(parameters[2])
                && parameters.size() == 3)) {
        Maps::getSymbolTable().find(parameters[0])->second = Maps::getSymbolTable().find(parameters[2])->second;
        if (Maps::getMapOfPath().count(parameters[0])) {
            Maps::getPathsValues().find(Maps::getMapOfPath().find(parameters[0])->second)->second =
                    Maps::getSymbolTable().find(parameters[0])->second;
            sendDataToServer(Maps::getMapOfPath().find(parameters[0])->second,
                             Maps::getSymbolTable().find(parameters[0])->second);// send new data to FlightGear
        }
    } else if ((Maps::getSymbolTable().count(parameters[0]) && onlyNum(parameters[2]) && parameters.size() <= 3)) {
        Maps::setSymbolTable(parameters[0], stod(parameters[2]));
        if (Maps::getMapOfPath().count(parameters[0])) {
            Maps::getPathsValues().find(Maps::getMapOfPath().find(parameters[0])->second)->second =
                    Maps::getSymbolTable().find(parameters[0])->second;
            sendDataToServer(Maps::getMapOfPath().find(parameters[0])->second,
                             Maps::getSymbolTable().find(parameters[0])->second);// send new data to FlightGear
        }
    } else if (((parameters[0] == "var" || Maps::getSymbolTable().count(parameters[0]))
                && lookForExpression(line))) {
        vector<string> splitted = splitToVarAndExpression(parameters);
        string toCalculate = replaceVarsWithValues(splitted[1]);
        ShuntingYardD yardD;
        double theResTinsert = yardD.infixToPrefix(toCalculate);
        Maps::getSymbolTable().find(splitted[0])->second = theResTinsert;
        if (Maps::getMapOfPath().count(splitted[0])) {
            Maps::getPathsValues().find(Maps::getMapOfPath().find(splitted[0])->second)->second = theResTinsert;
            sendDataToServer(Maps::getMapOfPath().find(splitted[0])->second, theResTinsert);//data to FlightGear
        } else {
            if (parameters[0] == "var") {
                Maps::setSymbolTable(parameters[1], theResTinsert);
            } else {
                Maps::setSymbolTable(parameters[0], theResTinsert);
            }
        }
    }

}

bool VarCommand::onlyNum(string &toChack) {
    for (int j = 0; j < toChack.size(); j++) {
        if (toChack[0] != '-' && (!isdigit(toChack[j]) && toChack[j] != '.')) {
            return false;
        }
    }
    return true;
}

bool VarCommand::lookForExpression(string toChack) {
    for (char i : toChack) {
        if (i == '+' || i == '-' || i == '*' || i == '/') {
            return true;
        }
    }
    return false;
}

vector<string> VarCommand::splitToVarAndExpression(vector<string> toSplit) {
    vector<string> result;
    string left, right;
    int i = 0;
    while (toSplit[i] != "=") {
        left += toSplit[i++];
    }
    result.push_back(left);
    i++;
    while (i < toSplit.size()) {
        right += toSplit[i++];
    }
    result.push_back(right);
    return result;
}

string VarCommand::replaceVarsWithValues(string toReplace) {
    for (auto &i : Maps::getSymbolTable()) {
        if (toReplace.find(i.first) != string::npos) {
            string str1 = toReplace.substr(0, toReplace.find(i.first));
            string str2 = toReplace.substr(toReplace.find(i.first) + i.first.length());
            string str3 = to_string(i.second);
            toReplace = str1 + str3 + str2;
        }
    }
    return toReplace;
}

void VarCommand::sendDataToServer(string path, double value) {
    ConnectCommand::deliverDateToServer(path, value);
}
