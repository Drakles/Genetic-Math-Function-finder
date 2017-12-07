//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#ifndef LISTA4_NODE_H
#define LISTA4_NODE_H

#include <string>

class Node {

    Node();
    Node(Node *node);

    Node(const Node &node);

    friend class Tree;

public:
    Node(const std::string &value, Node *parent);
    std::string toString();
    Node & operator=(Node &otherNode);
    ~Node();
    int getNumberOfVariables();
    std::string value;
private:
    Node *parent;
    Node *righChild;

    Node *leftChild;
    void getNumberOfVariables(Node *node, int &quantityOfVars);
    bool isOperator(std::string valueToCheck);

    bool isNumber(std::string valueToCheck);
};



#endif //LISTA4_NODE_H
