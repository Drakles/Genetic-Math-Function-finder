//
// Created by Kajetan Dymkiewicz on 04.12.2017.
//

#ifndef LISTA4_GODOFTHETREES_H
#define LISTA4_GODOFTHETREES_H


#include "../Generator/ExpressionGenerator.h"
#include "../Tree/Tree.h"


const int NUMBER_OF_GENERATIONS = 5;
const int MINIMAL_NUMBER_OF_TREES = 20;
const int INITIAL_POPULATION = 1000;

class GodOfTheTrees {

    friend class Tree;

public:
    int doTheGoding();

    bool exist = true;
private:
    ExpressionGenerator exprGen;
    queue<string> exprs;
    vector <Tree *> listOfTrees;
};


#endif //LISTA4_GODOFTHETREES_H
