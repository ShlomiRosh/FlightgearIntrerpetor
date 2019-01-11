#include "ShuntingYardD.h"

double ShuntingYardD::infixToPrefix(string infix) {

    vector<char> tokens(infix.begin(), infix.end());
    stack<double> numbers;
    stack<string> operators;
    char operand;
    Expression* left;
    Expression* right;

    for (int i = 0; i < infix.length(); i++) {
        if (isspace(tokens[i]))
            continue;
        if (isdigit(tokens[i])) {
            string number;
            while (i < infix.length() && (isdigit(tokens[i]) ) || tokens[i] == '.') {
                number += (tokens[i++]);
            }
            --i;
            numbers.push(stod(number));
        } else if (tokens[i] == '(') {
            operators.push(string(1,tokens[i]));
        } else if (tokens[i] == ')') {
            while (operators.top() != "(") {
                initializExpression(operand, left, right, operators, numbers);
                numbers.push(solveExpressions(left, operand, right));
            }
            operators.pop();
        } else if (isOperator(tokens[i])) {
            if (isOperator(tokens[i]) && isOperator(tokens[i + 1])) {//if we have -- skip on this operand Because of
                // the number after him need to be positive
                i++;
                continue;
            }
            while (!operators.empty() && getPriority(tokens[i], operators.top())) {
                initializExpression(operand, left, right, operators, numbers);
                numbers.push(solveExpressions(left, operand, right));
            }
            operators.push(string(1, tokens[i]));
        }
    }
    while (!operators.empty()) {
        initializExpression(operand, left, right, operators, numbers);
        numbers.push(solveExpressions(left, operand, right));
    }
    double result = numbers.top();
    numbers.pop();
    return result;
}

bool ShuntingYardD::isOperator(char oper) {
    return oper == '+' || oper == '-' || oper == '*' || oper == '/';
}

int ShuntingYardD::getPriority(const char &operand1, const string &operand2) const {
    if (operand2 == "(" || operand2 == ")") {
        return 0;
    }
    return !((operand2 == "-" || operand2 == "+") && (operand1 == '/' || operand1 == '*'));
}

double ShuntingYardD::solveExpressions(Expression *right, char operand, Expression *left) {
    if (operand == '+') {
        Plus plus(left,right);
        Number number(plus.calculate());
        return number.calculate();
    } else if (operand == '-') {
        Minus minus(left,right);
        Number number(minus.calculate());
        return number.calculate();
    } else if (operand == '*') {
        Mul mul(left,right);
        Number number(mul.calculate());
        return number.calculate();
    } else if (operand == '/') {
        Div div(left,right);
        Number number(div.calculate());
        return number.calculate();
    }
}

void ShuntingYardD::initializExpression(char &operand, Expression *&left, Expression *&right,
                                   stack<string> &operators, stack<double> &numbers) {
    operand = operators.top()[0];
    operators.pop();
    if (!numbers.empty()) {
        left = new Number(numbers.top());
        numbers.pop();
    }
    if (!numbers.empty()) {
        right = new Number(numbers.top());
        numbers.pop();
    }
}


