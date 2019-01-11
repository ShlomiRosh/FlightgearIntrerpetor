#ifndef SEMESTERPROJECT1TRY2_COMMAND_H
#define SEMESTERPROJECT1TRY2_COMMAND_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Command {

public:

    virtual void doCommand(vector<string> parameters, string line) = 0;

};

#endif //SEMESTERPROJECT1TRY2_COMMAND_H
