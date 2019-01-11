#ifndef SEMESTERPROJECT1TRY2_EXPRESSIONS_H
#define SEMESTERPROJECT1TRY2_EXPRESSIONS_H

#include "Expression.h"

class Number : public Expression {

public:

    explicit Number(double number);
    double calculate() const override;

private:

    double number;

};


class BinaryExpression : public Expression {

public:

    BinaryExpression(Expression* left, Expression* right);
    double calculate() const override = 0;

protected:

    Expression* left;
    Expression* right;

};


class Plus : public BinaryExpression {

public:

    Plus(Expression* left, Expression* right);
    double calculate() const override;

};


class Minus : public BinaryExpression {

public:

    Minus(Expression *left, Expression *right);
    double calculate() const override;

};


class Mul : public BinaryExpression {

public:

    Mul(Expression *left, Expression *right);
    double calculate() const override;

};


class Div : public BinaryExpression {

public:

    Div(Expression *left, Expression *right);
    double calculate() const override;

};

#endif //SEMESTERPROJECT1TRY2_EXPRESSIONS_H
