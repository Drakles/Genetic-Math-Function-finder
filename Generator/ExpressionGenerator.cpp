//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#include <cstdlib>
#include <iostream>
#include <random>
#include "ExpressionGenerator.h"


string genOperator(double whatToGenerate, double maxChanceOfGenerateSpecificOp){

    double chanceOfGenerateSpecificOp = maxChanceOfGenerateSpecificOp/12;

    while (whatToGenerate > maxChanceOfGenerateSpecificOp) whatToGenerate -= maxChanceOfGenerateSpecificOp;

    if(whatToGenerate < 2.5*chanceOfGenerateSpecificOp) return "*";
    if(2.5*chanceOfGenerateSpecificOp <= whatToGenerate && whatToGenerate < 5*chanceOfGenerateSpecificOp) return "/";
    if(5*chanceOfGenerateSpecificOp <= whatToGenerate && whatToGenerate < 7.5*chanceOfGenerateSpecificOp) return "+";
    if(7.5*chanceOfGenerateSpecificOp <= whatToGenerate && whatToGenerate < 10*chanceOfGenerateSpecificOp) return "-";
    if(10*chanceOfGenerateSpecificOp <= whatToGenerate && whatToGenerate < 11*chanceOfGenerateSpecificOp) return "sin";
    if(11*chanceOfGenerateSpecificOp <= whatToGenerate && whatToGenerate < 12*chanceOfGenerateSpecificOp) return "cos";
}

string genNumber(double generatedDouble){

    return to_string((int)generatedDouble/10);
}

string genVariable(double whatToGenerate, int minimumLevel){

    int diference = 97-minimumLevel; //23
    int generatedInFunctionNumber = (int)whatToGenerate+diference > 122 ? (int)whatToGenerate:(int)whatToGenerate+diference;

    char generatedVariable = (char)(generatedInFunctionNumber);
    string genVarInString(1,generatedVariable);

    return genVarInString;
}

queue < string > ExpressionGenerator::generateSetOfExprs(int quantityOfExpr, int howMuchVariables) {

    queue < string >queue;
    std::uniform_real_distribution<double> dis(0, 100);

    double whatToGenerate = dis(generator);

    for (int i = 0; i < quantityOfExpr ; ++i) {

        string expr;

        int varsToGen = howMuchVariables;
        int numbsToGen = 0;
        int opsToGen = varsToGen > 0 ? varsToGen-1 : 0;
        int quantityOfNumb = 0;
        int quantityOBinaryOp = 0;
        int quantityOfVars = 0;
        int numbOrVarsToGen;
        int symbolsGenerated = 0; // for information how much symbols are already generated
        bool treeOfOneSymbol = false;

        while((varsToGen > 0 || opsToGen >= 0 || numbsToGen > 0) && !treeOfOneSymbol && symbolsGenerated < 10){
            numbOrVarsToGen = varsToGen > numbsToGen ? varsToGen : numbsToGen;
            if(whatToGenerate <= CHANCE_OF_GENERATE_OP || (howMuchVariables > 1 && symbolsGenerated ==0)){
                expr.append(" ");
                expr.append((genOperator(whatToGenerate,CHANCE_OF_GENERATE_OP)));
                opsToGen--;
                quantityOBinaryOp++;
                symbolsGenerated++;
                if(quantityOBinaryOp + 1 > varsToGen ) numbsToGen++;
            }else {
                if (CHANCE_OF_GENERATE_OP < whatToGenerate && whatToGenerate < CHANCE_OF_GENERATE_NUMB + CHANCE_OF_GENERATE_OP && numbOrVarsToGen > 1) {
                    expr.append(" ");
                    expr.append((genNumber(whatToGenerate)));
                    if(quantityOBinaryOp == 0 && quantityOfVars == 0 && quantityOfNumb == 0) treeOfOneSymbol = true;
                    numbsToGen--;
                    quantityOfNumb++;
                    symbolsGenerated++;
                }else {
                    if (CHANCE_OF_GENERATE_VAR + CHANCE_OF_GENERATE_NUMB <= whatToGenerate && varsToGen > 0) {
                        expr.append(" ");
                        expr.append((genVariable(whatToGenerate,CHANCE_OF_GENERATE_VAR + CHANCE_OF_GENERATE_NUMB)));
                        if(quantityOBinaryOp == 0 && quantityOfVars == 0 && quantityOfNumb == 0) treeOfOneSymbol = true;
                        varsToGen--;
                        quantityOfVars++;
                        symbolsGenerated++;
                    }
                }
            }
            whatToGenerate = dis(generator);
        }
        expr.append(" ");
        queue.push(expr);
    }
    return queue;
}

ExpressionGenerator::ExpressionGenerator(){
    generator = std::mt19937(time(0));
}


