#include "Boolean.h"

Boolean::Boolean(string left, string operand, string right) {

    this->left = left;
    this->operand = operand;
    this->right = right;

}

bool Boolean::calculate() {
    if (this->operand == "<=") {
        return this->getNumFromStr(this->left) <= this->getNumFromStr(this->right);
    } else if (this->operand == ">=") {
        return this->getNumFromStr(this->left) >= this->getNumFromStr(this->right);
    } else if (this->operand == "==") {
        return this->getNumFromStr(this->left) == this->getNumFromStr(this->right);
    } else if (this->operand == "<") {
        return this->getNumFromStr(this->left) < this->getNumFromStr(this->right);
    } else if (this->operand == ">") {
        return this->getNumFromStr(this->left) > this->getNumFromStr(this->right);
    } else if (this->operand == "!=") {
        return this->getNumFromStr(this->left) != this->getNumFromStr(this->right);
    }
}

double Boolean::getNumFromStr(string &toCalc) {
    if (Maps::getSymbolTable().count(toCalc)) {
        return Maps::getSymbolTable().find(toCalc)->second;
    }
    return stod(toCalc);
}
