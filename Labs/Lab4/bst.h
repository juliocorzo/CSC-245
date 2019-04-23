#include "dsexceptions.h"
#include <iostream>

template<class Comparable>
class BinarySearchTree;

template<class Comparable>
class BinaryNode {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element(theElement), left(lt), right(rt) {}

    friend class BinarySearchTree<Comparable>;
};

template<class Comparable>
class BinarySearchTree {
public:
    explicit BinarySearchTree(const Comparable &notFound);
    BinarySearchTree(const BinarySearchTree &rhs);
    ~BinarySearchTree();
    Comparable findMin() const;
    Comparable findMax() const;
    Comparable find(const Comparable &x) const;
    bool isEmpty() const;
    void printTree() const;
    void postOrder() const;
    int height() const;
    int numLeaves() const;
    bool isBalanced() const;
    void makeEmpty();
    void insert(const Comparable &x);
    void remove(const Comparable &x);
    const BinarySearchTree &operator=(const BinarySearchTree &rhs);

private:
    BinaryNode<Comparable> *root;
    Comparable ITEM_NOT_FOUND;
    Comparable &elementAt(BinaryNode<Comparable> *t) const;
    void insert(const Comparable &x, BinaryNode<Comparable> *&t) const;
    void remove(const Comparable &x, BinaryNode<Comparable> *&t) const;
    BinaryNode<Comparable> *findMin(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *findMax(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *find(const Comparable &x, BinaryNode<Comparable> *t) const;
    void makeEmpty(BinaryNode<Comparable> *&t) const;
    BinaryNode<Comparable> *clone(BinaryNode<Comparable> *t) const;
    void printTree(BinaryNode<Comparable> *t) const;
    void postOrder(BinaryNode<Comparable> *t) const;
    int height(BinaryNode<Comparable> *t) const;
    int numLeaves(BinaryNode<Comparable> *t) const;
    bool isBalanced(BinaryNode<Comparable> *t) const;
};

#include "bst.cpp"
