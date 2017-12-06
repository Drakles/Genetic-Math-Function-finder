//
// Created by Kajetan Dymkiewicz on 04.12.2017.
//

#include "GodOfTheTrees.h"

bool compareTree(Tree* a,Tree* b){
    return (a->averageResult < b->averageResult);
}

int GodOfTheTrees::doTheGoding() {

    // INITIALIZATION
    exprs = exprGen.generateSetOfExprs(100000,HOW_MUCH_VARIABLE);
    while(!exprs.empty()){
        listOfTrees.push_back(new Tree(exprs.front()));
        exprs.pop();
    }
    // EVALUATION
    for (int i = 0; i < listOfTrees.size() ; ++i) {
//        cout << listOfTrees.at(i)->printAsTree() << endl;
        listOfTrees.at(i)->computeTreeAndSaveResult(listOfTrees.at(i)->getValuesOfVarsAndResultFromFile(FILE_PATH));
//        cout << listOfTrees.at(i)->averageResult<<endl;
    }
    std::sort (listOfTrees.begin(), listOfTrees.end(),compareTree);


    for (int m = 0; m < NUMBER_OF_GENERATIONS && !listOfTrees.size() < 20; ++m) {

        /* NATURAL SELECTION */

//        cout << "usunąłem połowę populacji najsłabszych bo okazałem się złym bogiem" << endl;
        for (int j = (int)listOfTrees.size()-1; j < listOfTrees.size() ; ++j) {
            delete listOfTrees.at(j);
        }
        listOfTrees.erase(listOfTrees.begin() + (int) listOfTrees.size() / 2, listOfTrees.end()); // delete half of population

        // MNOŻCIE SIE!
        for (int k = 0; k < listOfTrees.size(); ++k) {
            if (listOfTrees.size() > k + 1) {
                listOfTrees.at(k)->tryToReproduce(listOfTrees.at(k + 1), listOfTrees);
            }
        }
        std::sort(listOfTrees.begin(), listOfTrees.end(), compareTree);

        //MUTUJCIE SIE!
        for (int i = 0; i < listOfTrees.size(); ++i) {
            listOfTrees.at(i)->tryToModyfie(exprGen, listOfTrees);
        }
        std::sort(listOfTrees.begin(), listOfTrees.end(), compareTree);

    }

    cout << "UWAGA MAMY EWOLUCYJNEGO ZWYCIĘZCE!!!"<<endl;

    cout << "piersze miejsce:"<<endl;
    cout << listOfTrees.at(0)->printAsTree()<<endl;
    cout << listOfTrees.at(0)->printInOrder()<<endl;
    cout <<"wynik:"<<listOfTrees.at(0)->averageResult<<endl;

    cout << "drugie miejsce:"<<endl;
    cout << listOfTrees.at(1)->printAsTree()<<endl;
    cout << listOfTrees.at(1)->printInOrder()<<endl;
    cout <<"wynik:"<<listOfTrees.at(1)->averageResult<<endl;

    cout << "trzecie miejsce:"<<endl;
    cout << listOfTrees.at(2)->printAsTree()<<endl;
    cout << listOfTrees.at(2)->printInOrder()<<endl;
    cout <<"wynik:"<<listOfTrees.at(2)->averageResult<<endl;

}