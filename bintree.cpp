#include "bintree.h"

/** ===========================================================================
    Constructors/ Destructors
---------------------------------------------------------------------------- */
BinTree::BinTree(Node* root) : root(root) {}

BinTree::BinTree(const BinTree & rhs) {
    //root = nullptr;
    *this = rhs;
}

BinTree::~BinTree() {
    makeEmpty();
}

/** ===========================================================================
    Operator Overrides
---------------------------------------------------------------------------- */
ostream& operator<<(ostream& out, const BinTree& bt) {
    if (bt.isEmpty()) {
        cout << "! -- tree is empty -- !" << endl;
    } else {
        bt.inorder(out);
        out << endl;
    }
    return out;
}

void BinTree::inorder(ostream & out) const {
    inorderHelper(root, out);
}

void BinTree::inorderHelper(Node* n, ostream & out) const {
    if (n == nullptr) {
        return;
    }
    inorderHelper(n->left, out);
    out << *n->data << " ";
    inorderHelper(n->right, out);
}

BinTree& BinTree::operator=(const BinTree& rhs) {
    if (this != &rhs) {
        copySubtree(root, rhs.root);
    }
    return *this;
}

void BinTree::copySubtree(Node*& lhs, Node* rhs) {
    if (rhs == nullptr) {
        // nothing to copy, delete extra nodes, if any.
        pluck(lhs);
        return;
    }

    if (lhs == nullptr) {
        // needs child node. allocate memory.
        lhs = new Node();
        lhs->data = new NodeData(*rhs->data);
    } else {
        // existing child node. overwrite.
        *lhs->data = *rhs->data;
    }
    copySubtree(lhs->left, rhs->left);
    copySubtree(lhs->right, rhs->right);
}

bool BinTree::operator==(const BinTree& rhs) const {
    return checkEqual(root, rhs.root);
}

bool BinTree::checkEqual(const Node* n, const Node* rhs) const {
    // reached end of leaves without tests failing.
    // if either are null, but not both, they are not identical.
    if (n == nullptr && rhs == nullptr) return true;
    else if (n == nullptr ^ rhs == nullptr) return false;

    return checkEqual(n->left, rhs->left) &&
           checkEqual(n->right, rhs->right) && 
           *n->data == *rhs->data;
}

bool BinTree::operator!=(const BinTree& rhs) const {
    return !(*this == rhs);
}

/** ===========================================================================
    BinTree Functions
---------------------------------------------------------------------------- */
bool BinTree::isEmpty() const {
    return (root == nullptr);
}

void BinTree::makeEmpty(const bool& keep) {
    pluck(root, keep);
}

void BinTree::pluck(Node*& n, const bool& keepND) {
    if (n == nullptr) return;

    pluck(n->left, keepND);
    pluck(n->right, keepND);

    // delete node data.
    if (!keepND) {
        delete n->data;
        n->data = nullptr;
    }

    // delete node itself.
    delete n;
    n = nullptr;
}

bool BinTree::insert(NodeData* nd) {
    if (nd == nullptr) return false;

    return insert(nd, root);
}

bool BinTree::insert(NodeData* nd, Node*& n) {
    // ignore duplicates, insert if nullptr found.
    if (n == nullptr) {
        n = new Node();
        n->data = new NodeData(*nd);
        return true;
    } else if (*nd == *n->data) {
        return false;
    }

    // search left if smaller, right if bigger.
    Node*& next = (*nd < *n->data) ? n->left : n->right;
    return insert(nd, next);
}

bool BinTree::retrieve(const NodeData& target, NodeData*& ret) const {
    if (isEmpty()) return false;
    retrieve(root, target, ret);
    return (ret != nullptr);
}

bool BinTree::retrieve(
    const Node* n, const NodeData& target, NodeData*& ret) const {
    if (n == nullptr) {
        // not found.
        ret = nullptr; // so ret is not junk/ prev search destination
        return false;
    } else if (target == *n->data) {
        // found.
        ret = n->data;
        return true;
    }

    // perform binary search recursively through tree.
    Node* next = (target < *n->data) ? n->left : n->right;
    return retrieve(next, target, ret);
}

int BinTree::getDepth(const NodeData& target) const {
    return getDepth(root, target);
}

int BinTree::getDepth(const Node* n, const NodeData& target) const {
    if (n == nullptr) {
        return 0;
    }
    if (target == *n->data) {
        return 1;
    }

    int depth = getDepth(n->left, target);
    if (depth > 0) {
        return ++depth;
    }
    depth = getDepth(n->right, target);
    if (depth > 0) {
        return ++depth;
    }
}

void BinTree::bstreeToArray(NodeData * arr[]) {
    int* i = new int(0);
    bstreeToArray(root, arr, *i);
    delete i;
    i = nullptr;
    makeEmpty(true);
}

void BinTree::bstreeToArray(Node* n, NodeData * arr[], int & i) {
    if (n == nullptr) return;

    bstreeToArray(n->left, arr, i);
    arr[i++] = n->data;
    bstreeToArray(n->right, arr, i);
}

void BinTree::arrayToBSTree(NodeData * arr[]) {
    int lo = 0;
    int hi = findHi(arr); // last ELEMENT (aka length-1)
    if (hi - lo <= 0) {
        cout << "! -- Array is empty. Can't convert! -- !" << endl;
        return;
    }

    int mid = lo + (hi - lo) / 2;
    root = (root == nullptr) ? new Node : root;
    arrayToBSTree(arr, root, lo, hi);
}
void BinTree::arrayToBSTree(NodeData * arr[], Node*& n, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    // base case
    if (hi<lo || lo>hi) {
        // no elements to add. delete existing nodes, if any.
        pluck(n);
        return;
    }

    // transfer NodeData*, handling 2 special cases.
    if (mid == lo && mid == hi) {
        // 1 element remains: leaf. clear child nodes, if any.
        pluck(n->left);
        pluck(n->right);
    } else if (mid == lo) {
        // 2 elements remain: node with 1 child. n favors left-middle element.
        // delete left children, if existing. Logic places last child on right.
        pluck(n->left);
    }
    delete n->data;     // delete pre-existing data, if any.
    n->data = arr[mid]; // array transfers ownership of NodeData*
    arr[mid] = nullptr;

    // continue until entire array is transferred. allocate if can't recycle.
    n->left = (mid - 1 >= lo && n->left == nullptr) ? new Node() : n->left;
    n->right = (mid + 1 <= hi && n->right == nullptr) ? new Node() : n->right;
    arrayToBSTree(arr, n->left, lo, mid - 1);
    arrayToBSTree(arr, n->right, mid + 1, hi);
}

int BinTree::findHi(NodeData* arr[]) const {
    int i;
    for (i = 0; i < 100; i++) {
        if (i+1 == 100 || arr[i+1] == nullptr) break;
    }
    return i;
}


/** ===========================================================================
    Print functions
---------------------------------------------------------------------------- */

void BinTree::displaySideways() const {
    if (isEmpty()) {
        cout << "! -- cannot display empty tree -- !" << endl;
    }
    sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
    if (current != nullptr) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level 
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl; // display information of object
        sideways(current->left, level);
    }
}