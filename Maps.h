#ifndef UNTITLED4_MAPS_H
#define UNTITLED4_MAPS_H
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Maps {

public:

    static map<string, string> getMapOfPath();
    static void setMapOfPath(string kay, string path);
    static map<string, double> &getPathsValues();
    static void setPathsValues(string kayPath, double value);
    static map<string, double> &getSymbolTable();
    static void setSymbolTable(string kayVar, double value);
    static void initMapPathsValue();

private:

    static map<string, string> mapOfPath;
    static map<string, double> pathsValues;
    static map<string, double> symbolTable;

};

#endif //UNTITLED4_MAPS_H