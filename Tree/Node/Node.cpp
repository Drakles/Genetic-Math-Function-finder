//
// Created by Kajetan Dymkiewicz on 25.11.2017.
//

#include "Node.h"
#include "../Tree.h"

using namespace std;

Node::Node(const std::string &value, Node *parent){
    this->value = value;
    this->leftChild = nullptr;
    this->righChild = nullptr;
    this->parent = parent;
}

Node::Node(){
    this->leftChild= nullptr;
    this->righChild = nullptr;
    this->parent = nullptr;
}

std::string Node::toString(){
    return this->value;
}

Node& Node::operator=(Node &otherNode) {

//    parent = new Node(*otherNode.parent);
    value = otherNode.value;

    if (otherNode.leftChild != nullptr) {
        leftChild = new Node(*otherNode.leftChild);
    }

    if (otherNode.righChild != nullptr) {
        righChild = new Node(*otherNode.righChild);
    }
    return *this;
}

Node::~Node() {
    if(leftChild != nullptr) delete leftChild;
    if(righChild != nullptr) delete righChild;
}

Node::Node(Node *node) {
    if(node != nullptr){
        this->value = node->value;
        this->parent = node->parent;

        if(node->leftChild != nullptr){
            this->leftChild = new Node(*node->leftChild);
        }else this->leftChild = nullptr;
        if(node->righChild != nullptr){
            this->righChild = new Node(*node->righChild);
        }else this->righChild = nullptr;

    }
}

Node::Node(const Node &node) {
    if(&node != nullptr){
        this->value = node.value;
        this->parent = node.parent;

        if(node.leftChild != nullptr){
            this->leftChild = new Node(*node.leftChild);
        }else this->leftChild = nullptr;
        if(node.righChild != nullptr){
            this->righChild = new Node(*node.righChild);
        }else this->righChild = nullptr;

    }
}

void Node::getNumberOfVariables(Node *node, int &quantityOfVars){

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

int Node::getNumberOfVariables(){
    int quantityOfVars = 0;

    getNumberOfVariables(this,quantityOfVars);

    return quantityOfVars;
}

bool Node::isOperator(string valueToCheck){
    return (valueToCheck ==MULTPL_STRING || valueToCheck == DVSIN_STRING || valueToCheck == ADD_STRING
            || valueToCheck == SBSTR_STRING || valueToCheck == SIN || valueToCheck == COS);
}

bool Node::isNumber(string valueToCheck){
    bool isNumber = true;

    for (int i = 0; i < valueToCheck.length(); ++i) {
        if(!isdigit(valueToCheck[0])) isNumber = false;
    }
    return isNumber;
}