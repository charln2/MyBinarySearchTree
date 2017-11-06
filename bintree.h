/** ===========================================================================
    bintree.h
    Purpose: implement a Binary Search Tree

    Assumptions:
    Duplicate data is ignored when building or inserting into a tree.
    This class does not implement functions to remove individual nodes.

    Implementation tries to have as few memory allocations as possible,
    favoring the moving of pointers rather than allocating copies onto the
    heap, and copying a tree attempts to build on the tree that is already
    existing without initially clearing its memory.


    @author: Charlie Nguyen
    @version: 1.0
---------------------------------------------------------------------------- */
#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
#include <string>

class BinTree
{
    // operator<< method can access BinTree class' private properties
    friend ostream& operator<<(ostream& out, const BinTree& bt);
private:
    // Tree is composed of Node*s, which contain NodeData*s.
    struct Node {
        NodeData* data = nullptr;   // ptr to data obj
        Node* left = nullptr;		// ptr to left subtree
        Node* right = nullptr;	    // ptr to right subree
    };
public:
    /** =======================================================================
        Default constructor with an optional parameter.

        @param root Pointer to base tree node. Default is nullptr.
        -------------------------------------------------------------------- */
    BinTree(Node* root = nullptr);

    /** =======================================================================
        Copy constructor.

        @param rhs The tree to be copied.
        -------------------------------------------------------------------- */
    BinTree(const BinTree& rhs);

    /** =======================================================================
        Destructor.
        -------------------------------------------------------------------- */
    ~BinTree();

    /** =======================================================================
        Checks to see if the tree is empty.

        @return true if empty, false otherwise.
        -------------------------------------------------------------------- */
    bool isEmpty() const;

    /** =======================================================================
        A function that returns all allocated memory (Node and NodeData) of 
        the root and all its children back to the heap.

        This method also deletes the NodeData objects the Nodes point to
        unless the optional keepND parameter is set to true, in which case the
        responsibility for deleting the NodeData is transferred to the caller.

        @param keep if true, does not delete NodeData*. Default is false.
        -------------------------------------------------------------------- */
    void makeEmpty(const bool& keep = false);

    /** =======================================================================
        Assignment operator.
        Overwrites own data to match data from BinTree in the right-hand side.
        It attempts to allocate and deallocate as few resources as possible for
        maximum efficiency.

        @param rhs BinTree to be copied.
        -------------------------------------------------------------------- */
    BinTree& operator=(const BinTree& rhs);

    /** =======================================================================
        Checks if a BinTree is identical to its right-hand counterpart.
        Two BinTrees are equal when the relational order of their Nodes match
        exactly.
        This method does not assume that either tree is a Binary Search Tree,
        but both must be Binary Trees.

        @param rhs BinTree to compare against for equality.
        @return true if equal, false otherwise.
        -------------------------------------------------------------------- */
    bool operator==(const BinTree& rhs) const;

    /** =======================================================================
        Checks if a BinTree is NOT identical to its right-hand counterpart.

        @param rhs BinTree to compare against for non-equality.
        @return true if not equal, false otherwise.
        -------------------------------------------------------------------- */
    bool operator!=(const BinTree& rhs) const;

    /** =======================================================================
        Performs a binary search to insert a Node containing NodeData into the
        tree, starting from the root and ignoring duplicates.

        @param nd NodeData to be inserted.
        @return true if successful, false otherwise.
        -------------------------------------------------------------------- */
    bool insert(NodeData* nd);

    /** =======================================================================
        Helper function for operator<< to print NodeData objects in LNR order.

        @param out The stream to be printed on.
        -------------------------------------------------------------------- */
    void inorder(ostream& out) const;

    /**
        Finds the corresponding NodeData* in the tree matching the target.

        @param target The NodeData object to search for in the tree.
        @param ret The NodeData in the tree if found, nullptr otherwise.
        @return true if found, false otherwise.
        -------------------------------------------------------------------- */
    bool retrieve(const NodeData& target, NodeData*& ret) const;

    /** =======================================================================
        Finds the depth of the Node in the tree containing the target.

        This method does not assume the tree is a Binary Search Tree, and
        therefore must search all nodes before determining whether or not a
        match was found.

        @param target NodeData object to find depth of.
        @return depth of the tree. 0 is not found, 1 is root.
        -------------------------------------------------------------------- */
    int getDepth(const NodeData& target) const;

    /** =======================================================================
        A routine that fills an array of NodeData* by using an in-order
        traversal of the tree. It leaves the tree empty.

        Responsibility for freeing the memory of the NodeData*s is transferred
        from the BinTree to the array.

        (Since this is just for practice, a statically allocated array of 100
        nullptr elements is assumed to avoid size error checking)

        @params arr The array to be converted.
        -------------------------------------------------------------------- */
    void bstreeToArray(NodeData* arr[]);

    /** =======================================================================
        A routine that recursively builds a balanced BinTree from an already
        sorted array (assumed), leaving the array filled with nullptrs.

        The root of each subtree is taken to be the middle element of a given
        index range within the array. It favors the "lower-mid" index in the
        event that there are two middle values, resulting in the tree filling
        from the right to the left. Because of this, Nodes with only 1 child 
        will always have a nulllptr value for its this->left property.

        Responsibility for freeing the memory of the NodeData*s is transferred
        from the array back to the BinTree.

        @param arr The array to be converted to a BinTree.
        -------------------------------------------------------------------- */
    void arrayToBSTree(NodeData* arr[]);

    /** =======================================================================
        Gives a visual display of the tree, viewable by tilding your head to
        the left; hard coded displaying to standard output.
        -------------------------------------------------------------------- */
    void displaySideways() const; // prints tree. Tilt head to left.

private:
    Node* root = nullptr; // Root Node for entire BinTree

    /** =======================================================================
        A helper function called by operator<< that prints the BinTree's
        NodeData values in-order.

        @param n The current node.
        @param out The output stream to print the tree to.
        -------------------------------------------------------------------- */
    void inorderHelper(Node* n, ostream& out) const;

    /** =======================================================================
        Recursively performs a binary search to insert a Node containing
        NodeData into the tree, ignoring duplicates.

        @param nd NodeData to be inserted.
        @param n The current Node.
        @return true if inserted, false otherwise.
        -------------------------------------------------------------------- */
    bool insert(NodeData* nd, Node*& n);

    /** =======================================================================
        A helper function that recursively deletes a Node and all its children.

        This method also deletes the NodeData objects the Nodes point to
        unless the optional keepND parameter is set to true, in which case the
        responsibility for deleting the NodeData is transferred to the caller.

        @param n The pointer to the Node to be deleted, removing all children.
        @param keepND if true, does not delete NodeData*. Default is false.
        -------------------------------------------------------------------- */
    void pluck(Node*& n, const bool& keepND = false);

    /** =======================================================================
        A helper method used by the assignment operator to make a tree into a
        copy of its right-hand operand.

        It overwrites a Node's existing NodeData if one already exists.
        It allocates memory if the copy destination is nullptr.
        It deletes extra hanging nodes if nothing is left to copy.

        @param lhs The pointer to the current node of the tree (this)
        @param rhs The current node of the right-hand tree
        -------------------------------------------------------------------- */
    void copySubtree(Node*& lhs, Node* rhs);

    /** =======================================================================
        Helper function that recursively searches for the NodeData target.

        @param n The current node.
        @param target The node to be searched for.
        @param ret The pointer to the matching node, nullptr otherwise.
        @return true if found, false otherwise.
        -------------------------------------------------------------------- */
    bool retrieve(const Node* n, const NodeData& target, NodeData*& ret) const;

    /** =======================================================================
        Helper method which recursively finds the depth of the Node containing
        the target.

        @param n The current node being searched
        @param target NodeData to find the depth of
        @return height of the corresponding Node. 0 is not found, 1 is root.
        -------------------------------------------------------------------- */
    int getDepth(const Node* n, const NodeData& target) const;

    /** =======================================================================
        Helper method to recursively check if a tree is identical to its 
        right-hand operand. Two BinTrees are equal when the relational order 
        of their Nodes match exactly.
        This method does not assume that either tree is a Binary Search Tree,
        but both must be Binary Trees.

        @param n The current node of the tree to test for equality.
        @param rhs The node of the right-hand operand test for equality.
        @return true if equal, false otherwise.
        -------------------------------------------------------------------- */
    bool checkEqual(const Node* n, const Node* rhs) const;

    /** =======================================================================
        Helper method that recursively fills an array of NodeData* by using an 
        in-order traversal of the tree. It leaves the tree empty.

        Responsibility for freeing the memory of the NodeData*s is transferred
        from the BinTree to the array.

        (Since this is just for practice, a statically allocated array of 100
        nullptr elements is assumed to avoid size error checking)
        
        @param n The current node to transfer its NodeData* from.
        @param arr The array to be converted.
        @param i The current index of the array, marking the insertion point.
        -------------------------------------------------------------------- */
    void bstreeToArray(Node* n, NodeData* arr[], int& i);

    /** =======================================================================
        A helper method to recursively build a balanced BinTree from an already
        sorted array (assumed), leaving the array filled with nullptrs.
        -------------------------------------------------------------------- */
    void arrayToBSTree(NodeData* arr[], Node*& n, int lo, int hi);

    /** =======================================================================
        A helper method to find the last element of an array of size 100.
        Unused elements are nullptr.

        @param arr The array to find the last element of
        -------------------------------------------------------------------- */
    int findHi(NodeData* arr[]) const;

    /** =======================================================================
        A helper method to recursively give a visual display of the tree if
        you were to tilt their head to the left.

        @param current The current Node
        @param level the current level(depth) of the tree, root is 0.
        -------------------------------------------------------------------- */
    void sideways(Node* current, int level) const;
};
#endif