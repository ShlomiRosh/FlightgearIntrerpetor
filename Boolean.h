#ifndef SEMESTERPROJECT1TRY2_BOOLEAN_H
#define SEMESTERPROJECT1TRY2_BOOLEAN_H


#include <string>
#include "Maps.h"
using namespace std;
class Boolean {

public:

    Boolean(string left, string operand, string right);
    bool calculate();

private:

    string left;
    string right;
    string operand;
    double getNumFromStr(string &toCalc);

};



#endif //SEMESTERPROJECT1TRY2_BOOLEAN_H
