//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#ifndef LISTA4_EXPRESSIONGENERATOR_H
#define LISTA4_EXPRESSIONGENERATOR_H
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

static const int CHANCE_OF_GENERATE_OP = 25; //   = 33%
static const int CHANCE_OF_GENERATE_NUMB = 41; // = 33%
static const int CHANCE_OF_GENERATE_VAR = 33; //  = 33%

static const double CHANCE_OF_GENERATE_SPECIFIC_OP = 16.6666; // 100/6 since there is 6 different operators

static const int HOW_MUCH_VARIABLE = 2;

class ExpressionGenerator {
public:
    queue < string > generateSetOfExprs(int quantityOfExpr, int howMuchVariables);

    double generateRandomDoubleNumber(int rangeFrom, int rangeTo);

    ExpressionGenerator();

    std::mt19937 generator;
private:

};


#endif //LISTA4_EXPRESSIONGENERATOR_H
