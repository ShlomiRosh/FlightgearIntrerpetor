#ifndef SEMESTERPROJECT1TRY2_COMMANDS_H
#define SEMESTERPROJECT1TRY2_COMMANDS_H

#include "Command.h"
#include "Maps.h"
#include "ShuntingYardD.h"
class PrintCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;

};

class SleepCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;

};

class BindCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;

private:

    Maps maps;

};

class VarCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;

private:

    bool onlyNum(string &toChack);
    bool lookForExpression(string toChack);
    string replaceVarsWithValues(string toReplace);
    vector<string> splitToVarAndExpression(vector<string> toSplit);
    void sendDataToServer(string path, double value);

};

class ConnectCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;
    static void deliverDateToServer(string thePath, double itsValue);
    static void stopToConnect();

private:

    static int sockfd;

};

class OpenDateServerCommand : public Command {

public:

    void doCommand(vector<string> parameters, string line) override;
    static bool toConnect;

};


#endif //SEMESTERPROJECT1TRY2_COMMANDS_H
