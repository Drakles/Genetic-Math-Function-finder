//
// Created by Kajetan Dymkiewicz on 04.12.2017.
//

#include "GodOfTheTrees.h"

bool compareTree(Tree* a,Tree* b){
    return (a->averageResult < b->averageResult);
}

int GodOfTheTrees::doTheGoding() {

    exprs = exprGen.generateSetOfExprs(100000,HOW_MUCH_VARIABLE);
    while(!exprs.empty()){
        listOfTrees.push_back(new Tree(exprs.front()));
        exprs.pop();
    }

    for (int i = 0; i < listOfTrees.size() ; ++i) {
        cout << listOfTrees.at(i)->printAsTree() << endl;
        listOfTrees.at(i)->computeTreeAndSaveResult(listOfTrees.at(i)->getValuesOfVarsAndResultFromFile(FILE_PATH));
        cout << listOfTrees.at(i)->averageResult<<endl;
    }

    std::sort (listOfTrees.begin(), listOfTrees.end(),compareTree);

    cout <<endl;
    cout <<"_______________________________________"<<endl;
    cout <<"NAJLEPSZE DRZEWKA PRZED MUTACJO"<<endl;
    cout <<endl;

    for (int j = 0; j < 3; ++j) {
        cout << listOfTrees.at(j)->printAsTree() << endl;
        cout << listOfTrees.at(j)->averageResult<<endl;

    }

    for (int i = 0; i < listOfTrees.size() ; ++i) {
        listOfTrees.at(i)->tryToModyfie(exprGen,listOfTrees);
    }
    std::sort (listOfTrees.begin(), listOfTrees.end(),compareTree);

    cout <<endl;
    cout <<"_______________________________________"<<endl;
    cout << "NAJLEPSZE DRZEWKA PO MUTACJI"<<endl;
    cout <<endl;

    for (int j = 0; j < 3; ++j) {
        cout << listOfTrees.at(j)->printAsTree() << endl;
        cout << listOfTrees.at(j)->averageResult<<endl;

    }

    /* NATURAL SELECTION */

    listOfTrees.erase( listOfTrees.begin()+(int)listOfTrees.size()/2,listOfTrees.end()); // delete half
    cout << "usunąłem połowę populacji najsłabszych bo jestem złym bogiem"<<endl;
    for (int k = 0; k < listOfTrees.size() ; ++k) {
        if(listOfTrees.size() > k+1){
            listOfTrees.at(k)->tryToReproduce(listOfTrees.at(k+1),listOfTrees);
        }
    }

    std::sort (listOfTrees.begin(), listOfTrees.end(),compareTree);
    cout <<"WYNIK KRZYŻOWANIA!"<<endl;
    cout <<"_______________________________________"<<endl;


    for (int l = 0; l < 5 ; ++l) {
        cout << listOfTrees.at(l)->printAsTree()<<endl;
        cout << listOfTrees.at(l)->printInOrder()<<endl;
        cout << listOfTrees.at(l)->averageResult<<endl;

    }


}