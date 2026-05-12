// card_list.h
// Author: Noah Ruderman
// All class declarations related to defining a BST that represents a player's hand

// card_list.h
// Binary search tree header file for CS 24 pa01, copied from intbst.h from lab03 and changed variables

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include <iostream>
#include "card.h"
using namespace std;
class CardBST {
 private:
    struct Node {
	Card info;
	Node *left, *right, *parent;
	// useful constructor:
    Node(Card v = Card('c', 1)) : info(v), left(0), right(0), parent(0) { }
    };
    // just one instance variable (pointer to root node):
    Node *root;

 public:
    // ctor, dtor, insert and one print method already done in card_list.cpp:
    CardBST();                   // constructor
    ~CardBST();                  // destructor
    bool insert(Card value);     // insert value; return false if duplicate
    void printInOrder() const;       // print tree data in-order to cout
    bool contains(Card value) const;  // true if value is in tree
    bool remove(Card value);                    // deletes the Node containing the given value from the tree

    //iterator
    class Iterator {
    public:
        Card operator*() const;      // get the card at current position
        Iterator& operator++();      // move forward (successor)
        Iterator& operator--();      // move backward (predecessor)
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    private:
        Node* current;
        friend class CardBST;        // so CardBST can access current
        Iterator(Node* n) : current(n) {}
    };

    Iterator begin() const;   // smallest card
    Iterator end() const;     // past the largest (nullptr)
    Iterator rbegin() const;  // largest card
    Iterator rend() const;    // past the smallest (nullptr)

 private:
    // recursive utility functions for use by public methods above
    Node* getNodeFor(Card value, Node* n) const; // returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(Card value, Node* n);
    void printInOrder(Node *n) const;
    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(Card value) const;
    Node* getPredecessorNode(Card value) const;
};


//play game declaration
void playGame(CardBST& alice, CardBST& bob);

#endif