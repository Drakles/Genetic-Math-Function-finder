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

static const int HOW_MUCH_VARIABLE = 2;

class ExpressionGenerator {
public:
    queue < string > generateSetOfExprs(int quantityOfExpr, int howMuchVariables);
    ExpressionGenerator();
private:
    std::mt19937 generator;

};


#endif //LISTA4_EXPRESSIONGENERATOR_H
