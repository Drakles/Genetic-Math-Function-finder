//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#include "Tree.h"
#include "../Generator/ExpressionGenerator.h"
#include "../God/GodOfTheTrees.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

Tree::Tree(){
    root = new Node;
}

Tree::~Tree() {
    delete root;
}

Tree::Tree(string expr) {
    this->createTree(expr);
}


Tree::Tree(const Tree &tree) {
    this->root = new Node(*tree.root);
}



Tree::Tree(Node* root){
    this->root = new Node(root);
}

int Tree::createTree(string &expr){

    if(isExprCorrect(expr) == NUM_VAR_AND_NUM_OP_IS_CORRECT) {

        while (expr[0] == SPACE_CHAR) {
            expr = expr.substr(1, expr.length());
        }

        expr = expr.append(SPACE_STRING);

        if (isOperatorButNotSinOrCos(expr[0]) || isOperatorSinOrCos(expr.substr(0, 3))) {

            if (expr.substr(0, 3) == SIN || expr.substr(0, 3) == COS) {
                this->root = new Node(expr.substr(0, 3), root);
                expr = expr.substr(3, expr.length());
                createTree(root, root, expr);
                return CREATE_TREE_SUCCES;
            } else {

                this->root = new Node(expr.substr(0, 1), root);
                expr = expr.substr(1, expr.length());
                createTree(root, root, expr);
                return CREATE_TREE_SUCCES;
            }
        } else {
            this->root = new Node(expr, root);
            return CREATE_TREE_SUCCES;
        }
    }else{
        makeStringCorrect(expr);
        createTree(expr);
        return STRING_INCORRECT;
    }
}


void Tree::createTree(Node *&actualNode,Node *&parentNode,string &expr){

    if(expr.length() > 0) {
        if (actualNode == nullptr) {

            while(expr[0] == SPACE_CHAR){
                expr = expr.substr(1, expr.length());
            }

            if(expr.substr(0,3) == SIN || expr.substr(0,3) == COS ){
                actualNode = new Node(expr.substr(0, 3), parentNode);
                expr = expr.substr(3, expr.length());
            }else {

                string clearValue;

                clearValue.append(expr.substr(0,1));

                expr = expr.substr(1, expr.length());

                while (!isspace(expr.at(0)) && expr.length() > 0) {
                    clearValue.append(expr.substr(0, 1));
                    expr = expr.substr(1, expr.length());
                }

                actualNode = new Node(clearValue, parentNode);
            }
        }
        if (isOperator(actualNode->value)) {


            if(isOperatorSinOrCos(actualNode->value)){ // if value is sin or cos
                if(actualNode->leftChild == nullptr) createTree(actualNode->leftChild,actualNode,expr);
            }else {

                // if value is operator but not cos or sin then it should has two children
                if (actualNode->leftChild == nullptr) {
                    createTree(actualNode->leftChild, actualNode, expr);
                }
                if (actualNode->righChild == nullptr) {
                    createTree(actualNode->righChild, actualNode, expr);
                }
            }
        } else {
            createTree(actualNode->parent,parentNode->parent, expr);
        }
    }
}

Tree& Tree::operator+(Tree &otherTree){

    Tree *pc_result;

    pc_result = new Tree();
    pc_result->root = new Node(*this->root);

    Node * p;
    p = pc_result->root;


    while (p->leftChild->leftChild != nullptr){
        p = p->leftChild;
    }
    *p->leftChild = *otherTree.root;

    return *pc_result;
}

Tree & Tree::operator=(Tree &t){
    this->root = new Node(*t.root);
    return *this;
}

bool Tree::operator<(Tree &tree) {
    return this->averageResult<tree.averageResult;
}

void Tree::getVariables(Node *node, set<string> &setOfVariables){

    set<string>::iterator it;

    if(node->leftChild != nullptr){
        getVariables(node->leftChild,setOfVariables);
    }

    if(!isOperator(node->value) && !isNumber(node->value)){
        setOfVariables.insert(node->value);
    }
    if(node->righChild != nullptr){
        getVariables(node->righChild,setOfVariables);
    }
}

set<string> Tree::getVariables(){
    set<string> setOfVariables;

    getVariables(root,setOfVariables);

    return setOfVariables;
}

void Tree::getNumberOfVariables(Node *node, int &quantityOfVars){

    if(node->leftChild != nullptr){
        getNumberOfVariables(node->leftChild,quantityOfVars);
    }
    if(!isOperator(node->value) && !isNumber(node->value)){
        quantityOfVars++;
    }
    if(node->righChild != nullptr){
        getNumberOfVariables(node->righChild,quantityOfVars);
    }
}

int Tree::getNumberOfVariables(){
    int quantityOfVars = 0;

    getNumberOfVariables(root,quantityOfVars);

    return quantityOfVars;
}

double Tree::comp(Node *node,vector<double> &listOfValueOfVariables){
    if(node != nullptr) {
        if (isOperator(node->value)) {

            switch(node->value.at(0)){
                case MULTPL_CHAR:
                    return comp(node->leftChild,listOfValueOfVariables) * comp(node->righChild,listOfValueOfVariables);
                case DVSIN_CHAR:
                    return comp(node->leftChild,listOfValueOfVariables) / comp(node->righChild,listOfValueOfVariables);
                case ADD_CHAR:
                    return comp(node->leftChild,listOfValueOfVariables) + comp(node->righChild,listOfValueOfVariables);
                case SBSTR_CHAR:
                    return comp(node->leftChild,listOfValueOfVariables) - comp(node->righChild,listOfValueOfVariables);
                case S:
                    return sin((comp(node->leftChild,listOfValueOfVariables)*PI)/180);
                case C:
                    return cos((comp(node->leftChild,listOfValueOfVariables)*PI)/180);
            }
        }else{
            if(isNumber(node->value))return stoi(node->value);
            else{
                double value = listOfValueOfVariables.back();
                listOfValueOfVariables.pop_back();
                return value;
            }
        }
    }
}

double Tree::computeTree(vector<double> listOfValueOfVariables){
    return comp(root,listOfValueOfVariables);
}

void Tree::computeTreeAndSaveResult(vector < vector <double> > valuesOfVariables){

    for (int j = 0; j < valuesOfVariables.size() ; ++j) {
        computedResults.push_back(computeTree(valuesOfVariables[j]));
    }

    averageResult = 0;
    for (int i = 0; i < computedResults.size() ; ++i) {
        averageResult += std::abs(computedResults[i]-expectedResults[i]);
    }
    averageResult = averageResult/computedResults.size();
}

vector<double> Tree::getValuesOfVarsFromUser(){
    vector <double> listOfValuesOfVars;

    int numberOfVars = this->getNumberOfVariables();
    double valueOfVarFromUser;

    for (int i = 0; i < numberOfVars ; ++i) {
        cin >> valueOfVarFromUser;
        listOfValuesOfVars.push_back(valueOfVarFromUser);
    }
    return listOfValuesOfVars;
}

vector < vector <double> > Tree::getValuesOfVarsAndResultFromFile(string fileName){
    std::ifstream reader(fileName);
    vector < vector <double> > listOfVectors;

    double firstArg,secondArg, result;

    while(reader >> firstArg >> secondArg >> result){
        vector < double> valuesOfVars;
        valuesOfVars.push_back(firstArg);
        valuesOfVars.push_back(secondArg);
        expectedResults.push_back(result);
        listOfVectors.push_back(valuesOfVars);
    }

    reader.close();
    return listOfVectors;
}


bool Tree::isNumber(string valueToCheck){
    bool isNumber = false;

    for (int i = 0; i < valueToCheck.length(); ++i) {
        if(isdigit(valueToCheck[0])) isNumber = true;
    }
    return isNumber;
}

int Tree::isExprCorrect(string expr){
    int numberOfOperators = 0;
    int numberOfVariables = 0;

    expr.append(SPACE_STRING);

    while(expr.length()>1){

        while(expr[0] == SPACE_CHAR && expr.length() > 1){
            expr = expr.substr(1, expr.length());
        }
        if(isOperatorButNotSinOrCos(expr.at(0))) {
            numberOfOperators++;
            expr = expr.substr(1, expr.length());
        }else {
            if (isOperatorSinOrCos(expr.substr(0, 3))) {
                numberOfOperators++;
                expr = expr.substr(3, expr.length());
            } else if(!isspace(expr.at(0))){
                numberOfVariables++;
                expr = expr.substr(1, expr.length());
            }
        }
    }
    return (numberOfVariables-numberOfOperators);
}

void Tree::makeStringCorrect(string &expr){

    if(isExprCorrect(expr) < NUM_VAR_AND_NUM_OP_IS_CORRECT) {
        while (isExprCorrect(expr) != NUM_VAR_AND_NUM_OP_IS_CORRECT) {
            expr.append(SPACE_STRING);
            expr.append(ONE);
        }
    }else{
        while (isExprCorrect(expr) != NUM_VAR_AND_NUM_OP_IS_CORRECT) {
            expr= expr.substr(0,expr.length()-1);
        }
    }
}

bool Tree::isOperator(string valueToCheck){
    return (valueToCheck ==MULTPL_STRING || valueToCheck == DVSIN_STRING || valueToCheck == ADD_STRING
            || valueToCheck == SBSTR_STRING || valueToCheck == SIN || valueToCheck == COS);
}


bool Tree::isOperatorButNotSinOrCos(char valueToCheck){
    return (valueToCheck ==MULTPL_CHAR || valueToCheck == DVSIN_CHAR || valueToCheck == ADD_CHAR || valueToCheck == SBSTR_CHAR);
}

bool Tree::isOperatorSinOrCos(string operatorToCheck){
    return (operatorToCheck == SIN || operatorToCheck ==COS);
}

Node*& Tree::findNodeToAttachedTree(Node *&node){
    if(node->leftChild != nullptr) findNodeToAttachedTree(node->leftChild);
    else{
        return node;
    }
}


int Tree::height() {
    return height(root);
}

int Tree::height(Node *node) {
    if (node == nullptr) {
        return -1;
    } else {
        int left = height(node->leftChild);
        int right = height(node->righChild);

        return left > right ? left+1 : right+1;
    }
}

void Tree::tryToModyfie(ExpressionGenerator& gen,vector <Tree *>& listOfTrees){
    std::mt19937 generator (time(0));
    std::uniform_real_distribution<double> dis(0, 100);

    double generatedChance = dis(generator);
    bool treeMutated = false;
    if(generatedChance <= CHANCE_OF_MUTATE){
        std::uniform_real_distribution<double> dis1(0,1);
        mutateTree(root,treeMutated,generator,dis1,gen,listOfTrees);
        this->computeTreeAndSaveResult(getValuesOfVarsAndResultFromFile(FILE_PATH));
    }
}

void Tree::mutateTree(Node *&node, bool &treeIsMutated,std::mt19937 generator,std::uniform_real_distribution<double> dis,
                      ExpressionGenerator& gen,vector <Tree *>& listOfTrees){
    int totalChance = this->getNumberOfNodesAndLeafses();
    double chanceOfOneNodeorLeafToMutate = 1/(double)totalChance;
    double generatedChance = dis(generator);

    if(generatedChance < chanceOfOneNodeorLeafToMutate && !treeIsMutated && averageResult != 0){

        int numberOfVarsInSubTree = node->getNumberOfVariables();
        int numberOfVarsInWholeTree = this->getNumberOfVariables();
        Tree subTree(gen.generateSetOfExprs(1,HOW_MUCH_VARIABLE-(numberOfVarsInWholeTree - numberOfVarsInSubTree)).front());

        delete node;
        node = new Node(*subTree.root);
        treeIsMutated = true;
    }else{
        if(node->righChild != nullptr) mutateTree(node->righChild,treeIsMutated,generator,dis,gen,listOfTrees);
        if(node->leftChild != nullptr) mutateTree(node->leftChild,treeIsMutated,generator,dis,gen,listOfTrees);
    }
}

int Tree::numberOfNodesAndLeafs(Node *node) {
    int nodes = 1;
    if (node->righChild != nullptr) nodes += numberOfNodesAndLeafs(node->righChild);
    if (node->leftChild != nullptr) nodes += numberOfNodesAndLeafs(node->leftChild);
    return nodes;
}

int Tree::getNumberOfNodesAndLeafses() {
    return numberOfNodesAndLeafs(root);
}

void Tree::tryToReproduce(Tree *& partnerTree, vector<Tree *> &listOfTrees) {
    std::mt19937 generator (time(0));
    std::uniform_real_distribution<double> dis(0, 100);

    double generatedChance = dis(generator);
    if(generatedChance <= CHANCE_OF_REPRODUCE){

        Tree* cloneOfThisTree(this);
        Tree* cloneOfPartnerTree(partnerTree);

        Tree* secondCloneOfThisTree(this);
        Tree* secondPartnerTree(partnerTree);
        bool treeReproduced = false;
        tryToChangeOneOfSubtreeForPartnerSubtree(cloneOfThisTree->root,cloneOfPartnerTree,generator,dis,treeReproduced);
        treeReproduced = false;
        tryToChangeOneOfSubtreeForPartnerSubtree(secondPartnerTree->root,secondCloneOfThisTree,generator,dis,treeReproduced);

        //dodaj dzieci do listy
        listOfTrees.push_back(cloneOfThisTree);
        // i wylicz nowe drzewka
        listOfTrees.at(listOfTrees.size()-1)
                ->computeTreeAndSaveResult(listOfTrees.at(listOfTrees.size()-1)->getValuesOfVarsAndResultFromFile(FILE_PATH));
        // i to samo dla drugiego drzewka
        listOfTrees.push_back(secondPartnerTree);
        listOfTrees.at(listOfTrees.size()-1)
                ->computeTreeAndSaveResult(listOfTrees.at(listOfTrees.size()-1)->getValuesOfVarsAndResultFromFile(FILE_PATH));

    }
}


void Tree::tryToChangeOneOfSubtreeForPartnerSubtree(Node *& node,Tree *& partnerTree, std::mt19937 generator, std::uniform_real_distribution<double> dis,
                                              bool &treeReproduced){
    int totalChanceOfReproduce = this->getNumberOfNodesAndLeafses();
    double chanceOfOneSubtreeToReproduce = 1/(double)totalChanceOfReproduce;
    double generatedChance = dis(generator);

    if(generatedChance < chanceOfOneSubtreeToReproduce && !treeReproduced && averageResult != 0){
        delete node;
        node = partnerTree->root;
        treeReproduced = true;
    }else{
        if(node->leftChild != nullptr) tryToChangeOneOfSubtreeForPartnerSubtree(node->leftChild,partnerTree,generator,dis,treeReproduced);
        if(node->righChild != nullptr) tryToChangeOneOfSubtreeForPartnerSubtree(node->righChild,partnerTree,generator,dis,treeReproduced);
    }
}

Node * Tree::tryToFindSubTreeFromParent(Node*& node,std::mt19937 generator,
                                              std::uniform_real_distribution<double> dis, bool &nodeReturned){
    if(node != nullptr) {
        //znajdz losowo subtree i je zwroc

        int totalChance = this->getNumberOfNodesAndLeafses();
        double chanceOfOneNodeorLeafToMutate = 1 / (double) totalChance;
        double generatedChance = dis(generator);

        if (generatedChance < chanceOfOneNodeorLeafToMutate && !nodeReturned && averageResult != 0) {
            nodeReturned = true;
            return new Node(node);
        } else {
            if (node->righChild != nullptr) tryToFindSubTreeFromParent(node->righChild, generator, dis, nodeReturned);
            if (node->leftChild != nullptr) tryToFindSubTreeFromParent(node->leftChild, generator, dis, nodeReturned);
        }
    }
}
/* metoda na potrzeby modyfikacji
void Tree::startMutateWithSameStruct(){
    std::mt19937 generator (time(0));
    std::uniform_real_distribution<double> dis(0, 10);

    double generatedChance = dis(generator);

    vMutateSaveStruct(this->root,generator,dis);

}


string genSinOrCos(string value){
    if(value == "cos"){
        return "sin";
    }else return "cos";
}

string genOperatorButNotSinOrCos(double whatToGenerate,string value,std::mt19937 generator,
                                 std::uniform_real_distribution<double> dis){

    bool stringReturned = false;

    while(!stringReturned) {
        if (whatToGenerate < 2.5 && value != "*"){
            stringReturned = true;
            return "*";
        }
        if (2.5 <= whatToGenerate && whatToGenerate < 5 && value != "/"){
            stringReturned = true;
            return "/";
        }
        if (5 <= whatToGenerate && whatToGenerate < 7.5 && value != "+"){
            stringReturned = true;
            return "+";
        }
        if (7.5 <= whatToGenerate && value != "-"){
            stringReturned = true;
            return "-";
        }
        whatToGenerate = dis(generator);
    }
}

string genVariable(double whatToGenerate,string value,std::mt19937 generator,
                   std::uniform_real_distribution<double> dis){

//    cout <<"whatToGenerate:"<<whatToGenerate<<endl;
    whatToGenerate *= 10;

    while(whatToGenerate > 122){
        whatToGenerate--;
    }
    while(whatToGenerate < 97){
        whatToGenerate++;
    }
//    cout <<"Teraz whatToGenerate:"<<whatToGenerate<<endl;
    int generatedInFunctionNumber = (int)whatToGenerate;
    char generatedVariable = (char)(generatedInFunctionNumber);
    string genVarInString(1,generatedVariable);

//    cout << "wyszło mi "<<genVarInString<<endl;
    if(genVarInString == value){
//        cout <<"jest taki sam"<<endl;
        whatToGenerate += 1;
        generatedInFunctionNumber = (int)whatToGenerate;
        generatedVariable = (char)(generatedInFunctionNumber);
        string genVarInString(1,generatedVariable);
//        cout << "wiec zwracam "<<genVarInString<<endl;
        return genVarInString;
    }
//    cout << "zwracam:"<<genVarInString<<endl;
    return genVarInString;
}

double genNumber(string value,double whatToGenerate){
    double number = stoi(value);
    if(number == whatToGenerate){
        return number/whatToGenerate;
    }else return whatToGenerate;
}

void Tree::vMutateSaveStruct(Node *& node, std::mt19937 generator,
                             std::uniform_real_distribution<double> dis){
    if(node != nullptr) {
        double generatedChance = dis(generator);
        if (isOperatorSinOrCos(node->value)) {
            node->value = genSinOrCos(node->value);
        } else if (isOperator(node->value)) {
            node->value = genOperatorButNotSinOrCos(generatedChance,node->value,generator,dis);
        } else if (isNumber(node->value)) {
            node->value = to_string(genNumber(node->value,generatedChance));
        } else node->value = genVariable(generatedChance,node->value,generator,dis);

        if(node->righChild != nullptr) vMutateSaveStruct(node->righChild,generator,dis);
        if(node->leftChild != nullptr) vMutateSaveStruct(node->leftChild,generator,dis);
    }
}
*/

/* PRINTING FUNCTIONS ------------------------------------------------------------------------------------------------*/

void Tree::printBinaryTree(Node *node, int level,string &output) {
    if (node == nullptr) {
        return;
    }
    if(node->righChild != nullptr) printBinaryTree(node->righChild, level + 1,output);
    if (level != 0) {
        for (int i = 0; i < level - 1; i++)
            output.append("|\t\t");
        output.append("|-------");
        output.append(node->value);
    } else
        output.append(node->value);
    output.append("\n");;
    if(node->leftChild != nullptr) printBinaryTree(node->leftChild, level + 1,output);
}

string Tree::printAsTree() {
    string output;
    printBinaryTree(root, 0,output);
    return output;
}

string Tree::printPostOrder(){
    string output = "";
    printPostOrder(root,output);
    return output;
}

void Tree::printPostOrder(Node *node,string &output) {
    output.append(node->value);
    output.append(SPACE_STRING);

    if(node->leftChild != nullptr) printPostOrder(node->leftChild,output);
    if(node->righChild != nullptr) printPostOrder(node->righChild,output);
}

string Tree::printVariables(set<string> setOfVariables){

    string output = "";
    set<string>::iterator it;

    for (it = setOfVariables.begin(); it!=setOfVariables.end() ; it++) {
        output.append(*it);
        output.append(",");
    }
    return output;
}

string Tree::printInOrder() {
    string output= "";
    printInOrder(root,output);
    return output;
}

void Tree::printInOrder(Node *node, string &output) {
    if(node->leftChild != nullptr){
        printInOrder(node->leftChild,output);
    }
    output.append(node->value);
    output.append(SPACE_STRING);
    if(node->righChild != nullptr){
        printInOrder(node->righChild,output);
    }
}
