#include "Expressions.h"

//class Number
Number::Number(double number) {
    this->number = number;
}

double Number::calculate() const {
    return this->number;
}

//class BinaryExpression
BinaryExpression::BinaryExpression(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}

//class Plus
Plus::Plus(Expression *left, Expression *right) : BinaryExpression(left, right) {}

double Plus::calculate() const {
    return left->calculate() + right->calculate();
}

//class Minus
Minus::Minus(Expression *left, Expression *right) : BinaryExpression(left, right) {}

double Minus::calculate() const {
    return left->calculate() - right->calculate();
}

//class Mul
Mul::Mul(Expression *left, Expression *right) : BinaryExpression(left, right) {}

double Mul::calculate() const {
    return left->calculate() * right->calculate();
}

//class Div
Div::Div(Expression *left, Expression *right) : BinaryExpression(left, right) {}

double Div::calculate() const {
    if (this->right->calculate() == 0.0) {
        throw ("can't divide by zero");
    }
    return left->calculate() / right->calculate();
}
