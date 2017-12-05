//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#ifndef LISTA4_TREE_H
#define LISTA4_TREE_H
#include "Node/Node.h"
#include "../Generator/ExpressionGenerator.h"
#include <string>
#include <set>
#include <vector>
#include <random>

using namespace std;
#define PI 3.14159265

const int NUM_VAR_AND_NUM_OP_IS_CORRECT = 1;

const char SPACE_CHAR = ' ';
const string SPACE_STRING = " ";

const char MULTPL_CHAR ='*';
const char DVSIN_CHAR = '/';
const char ADD_CHAR = '+';
const char SBSTR_CHAR = '-';
const string MULTPL_STRING ="*";
const string DVSIN_STRING = "/";
const string ADD_STRING = "+";
const string SBSTR_STRING = "-";

const string SIN = "sin";
const string COS = "cos";
const char S = 's';
const char C = 'c';

const string ONE = "1";

const int STRING_INCORRECT = -1;
const int CREATE_TREE_SUCCES = 0;

const int CHANCE_OF_MUTATE = 60; // 60%
const int CHANCE_OF_REPRODUCE = 50; //50%
const string FILE_PATH = "/Users/Drakles/Documents/nauka/Semestr III/ZMPO/Lista4/args.txt";

class Tree {


    Tree(Node *root);

    friend class Node;

public:

    Tree(const Tree &tree);
    Tree();
    Tree(string expr);
    ~Tree();

    int createTree(string &expr);
    string printAsTree();
    set<string> getVariables();
    Tree & operator=(Tree &t);
    Tree& operator+(Tree &tree);
    bool operator<(Tree & tree);
    double computeTree(vector<double> listOfValueOfVariables);
    int isExprCorrect(string expr);
    void makeStringCorrect(string &expr);
    int height();
    string printPostOrder();
    int getNumberOfVariables();
    vector<double> getValuesOfVarsFromUser();
    vector < vector <double> >getValuesOfVarsAndResultFromFile(string fileName);
    string printVariables(set<string> setOfVariables);
    void computeTreeAndSaveResult(vector < vector <double> > listOfValueOfVariables);
    int getNumberOfNodesAndLeafses();
    vector<double> computedResults;
    vector<double> expectedResults;
    void tryToModyfie(ExpressionGenerator& gen,vector <Tree *>& listOfTrees);
    void tryToReproduce(Tree *& partnerTree, vector <Tree *>& listOfTrees);
    string printInOrder();

    double averageResult;
private:
    Node *root;
    void printPostOrder(Node *node, string &output);
    void createTree(Node *&actualNode, Node *&parentNode, string &expr);
    double comp(Node *node, vector<double> &listOfValueOfVariables);
    bool isOperator(string valueToCheck);
    bool isOperatorSinOrCos(string operatorToCheck);
    bool isOperatorButNotSinOrCos(char valueToCheck);
    bool isNumber(string valueToCheck);
    void getVariables(Node *node, set<string> &setOfVariables);
    Node *&findNodeToAttachedTree(Node *&node);
    void printBinaryTree(Node *node, int level, string &output);
    int height(Node *node);
    void getNumberOfVariables(Node *node, int &quantityOfVars);
    int numberOfNodesAndLeafs(Node *node);
    void mutateTree(Node *&node, bool &treeIsMutated,
                    std::__1::mersenne_twister_engine<uint_fast32_t, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> generator,
                    std::__1::uniform_real_distribution<double> dis,ExpressionGenerator& gen,vector <Tree *>& listOfTrees);
    Node *
    tryToFindSubTreeFromParent(Node *&node, mt19937 generator, uniform_real_distribution<double> dis, bool &nodeReturned);

    void reproduceTwoTrees(Node *&node, Node *&nodeToAttached, mt19937 generator, uniform_real_distribution<double> dis,
                           bool &nodeAttached);
    void printInOrder(Node *node, string &output);

};


#endif //LISTA4_TREE_H
