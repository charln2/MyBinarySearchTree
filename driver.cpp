/** ===========================================================================
    driver.cpp
    Purpose: serves as the driver for the project.

    Input taken from "data2.txt" is used to build and put BinTrees through 
    simple test cases.

    @author: Dr. Carol Zander (with modifications by Charlie Nguyen)
    @version: 1.0
---------------------------------------------------------------------------- */
#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

static const int ARRAYSIZE = 100;
//global function prototypes
void buildTree(BinTree&, ifstream&);      
void initArray(NodeData*[]);             // initialize array to NULL
void clearArray(NodeData*[]);
void printArray(NodeData*[]);
void printTree(const BinTree&);

int main() {
    // create file object infile and open it
    // for testing, call your data file something appropriate, e.g., data2.txt
    ifstream infile("data2.txt");
    if (!infile) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    // the NodeData class must have a constructor that takes a string
    NodeData notND("not");
    NodeData andND("and");
    NodeData sssND("sss");
    NodeData eND("e");
    NodeData mND("m");
    NodeData tND("t");

    BinTree T, T2, dup;
    NodeData* ndArray[ARRAYSIZE];
    initArray(ndArray);
    cout << "Initial data:" << endl << "  ";
    buildTree(T, infile);              // builds and displays initial data
    cout << endl;
    BinTree first(T);                  // test copy constructor
    dup = dup = T;                     // test operator=, self-assignment
    while (!infile.eof()) {
        cout << "Tree Inorder:" << endl << T; // operator<< does endl
        T.displaySideways();

        // test retrieve 
        NodeData* p;      // pointer of retrieved object
        bool found;       // whether or not object was found in tree
        found = T.retrieve(andND, p);
        cout << "Retrieve --> and:  " << 
            (found ? "found" : "not found") << endl;
        found = T.retrieve(notND, p);
        cout << "Retrieve --> not:  " << 
            (found ? "found" : "not found") << endl;
        found = T.retrieve(sssND, p);
        cout << "Retrieve --> sss:  " << 
            (found ? "found" : "not found") << endl;

        // test getDepth 
        cout << "Depth    --> and:  " << T.getDepth(andND) << endl;
        cout << "Depth    --> not:  " << T.getDepth(notND) << endl;
        cout << "Depth    --> sss:  " << T.getDepth(sssND) << endl;

        // test ==, and != 
        T2 = T;
        cout << "T == T2?     " << 
            (T == T2 ? "equal" : "not equal") << endl;
        cout << "T != first?  " << 
            (T != first ? "not equal" : "equal") << endl;
        cout << "T == dup?    " << 
            (T == dup ? "equal" : "not equal") << endl;
        dup = T;

        // TREE ==> ARRAY
        T.bstreeToArray(ndArray);
        cout << "Tree ==> Array. \
            \nArray should be full, Tree should be empty:" << endl;
        printArray(ndArray);
        printTree(T);

        // ARRAY ==> TREE
        T.arrayToBSTree(ndArray);
        cout << "Array ==> Tree. \
            \nArray should be empty, Tree should be full:" << endl;
        printArray(ndArray);
        printTree(T);

        // --------------------------------------------------------------------
        // setup next test
        T.makeEmpty();                  // empty out the tree
        clearArray(ndArray);            // delete non-null tree data, null all
        cout << "-------------------------------------------------------------"
            << endl;
        cout << "Initial data:" << endl << "  ";
        buildTree(T, infile);
        cout << endl;
    }
    infile.close();
    clearArray(ndArray);        

    return 0;
}

/** ===========================================================================
    BuildTree    
    To build a tree, read strings from a line of input in a text file, 
    terminating when "$$" is encountered. Each input string is printed to cout.
    
    Since there is some work to do before the actual insert that is
    specific to the client problem, it's best that building a tree is not a 
    member function (it's not strictly ADT). It's a global function. 
---------------------------------------------------------------------------- */
void buildTree(BinTree& T, ifstream& infile) {
    string s;

    while(true) {
        infile >> s;
        cout << s << ' ';
        if (s == "$$" || infile.eof()) break; // at end of tree instruc/ file
        NodeData* ptr = new NodeData(s); // NodeData constructor takes string
        // could do a setData that reads a string to keep it object-oriented

        bool success = T.insert(ptr);
        if (!success)
            delete ptr;                       // duplicate case, not inserted 
    }
}


/** ===========================================================================
    initialize the array of NodeData* to nullptr
---------------------------------------------------------------------------- */
void initArray(NodeData* ndArray[]) {
    for (int i = 0; i < ARRAYSIZE; i++) {
        ndArray[i] = nullptr;
    }
}

/** ===========================================================================
    deallocates all data from an already initialized array.
---------------------------------------------------------------------------- */
void clearArray(NodeData* ndArray[]) {
    for (int i = 0; i < ARRAYSIZE && ndArray[i] != nullptr; i++) {
        delete ndArray[i];
        ndArray[i] = nullptr;
    }
}

/** ===========================================================================
    Prints the contents of the array for debugging purposes.
---------------------------------------------------------------------------- */
void printArray(NodeData* ndArray[]) {
    cout << "Array contents: ";
    for (int i = 0; i < ARRAYSIZE; i++) {
        NodeData* nd = ndArray[i];
        if (nd != nullptr) {
            cout << *nd << " ";
        }
    }
    cout << endl;
}

/** ===========================================================================
    Prints the contents of the tree for debugging purposes.
---------------------------------------------------------------------------- */
void printTree(const BinTree& t) {
    cout << "Tree contents: " << endl;
    cout << t;
    t.displaySideways();
}
