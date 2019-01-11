#ifndef SEMESTERPROJECT1TRY2_SHUNTINGYARDD_H
#define SEMESTERPROJECT1TRY2_SHUNTINGYARDD_H

#include <iostream>
#include <stack>
#include <vector>
#include "Expression.h"
#include "Expressions.h"

using namespace std;

class ShuntingYardD {

public:

    double infixToPrefix(string infix);
    bool isOperator(char oper);
    int getPriority(const char &operand1, const string &operand2) const;
    double solveExpressions(Expression* left, char operand, Expression* right);
    void initializExpression(char &operand, Expression* &left, Expression* &right,
                             stack<string> &operators, stack<double> &numbers);
};


#endif //SEMESTERPROJECT1TRY2_SHUNTINGYARDD_H
