// card_list.cpp
// Author: Noah Ruderman
// Implementation of the classes defined in card_list.h

// copied and pasted from lab03 intbst.cpp but removed unnecessary functions 
// like summation and then changed intBST to CardBST and ints to Card objects

#include "card_list.h"

#include <iostream>
using std::cout;
using namespace std; //adding this because I am used to it

// constructor sets up empty tree
CardBST::CardBST() { 
    root = NULL; //since we are already doing CardBST:: it's already accessing the class which contains the root pointer, since it is defined as a pointer
    // doing root instead of *root gives us the pointer itself, not the key in the root.
}

// destructor deletes all nodes, using the recursive clear helper function
CardBST::~CardBST() {
    clear(root);
}

// recursive helper for destructor
void CardBST::clear(Node *n) {
    if (n) { // checks if the pointer to the node exists, then go in and clear the left, clear the right, and delete the node itself
        // this way also if n is null (i.e. we go into the left child but it doesn't exist) then nothing happens and it doesn't break
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(Card value) {
    // check the root first, since we need to set it if the tree is empty
    if (!root) {
        root = new Node(value);
        return true; 
    }
    return insert(value, root); 
}

// recursive helper for insert
bool CardBST::insert(Card value, Node* n) {
    if (value == n->info) { 
        return false; // value is a duplicate
    } 
    
    if (value < n->info) {
        // look to left if less than current node
        if (n->left != NULL) {
            return insert(value, n->left); // if there is something there, reurse
        } else {
            // nothing here! add the node and link it
            n->left = new Node(value);
            n->left->parent = n; 
            return true;
        }
    } else { //same thing but on the right (value is now greater than current node)
        if (n->right != NULL) {
            return insert(value, n->right); // recurse
        } else {
            n->right = new Node(value);
            n->right->parent = n; 
            return true;
        }
    }
}

// print tree data in-order, with helper
void CardBST::printInOrder() const {
    printInOrder(root); //calls the recursive helper function, starting with the root node
}
void CardBST::printInOrder(Node *n) const {
    //base case
    if (!n) {
        return; //if there is no node, then we are done and we can return
    }

    printInOrder(n->left); //recurse on the left
    cout << n->info << endl; // print the parent, added endl since each card on own line
    printInOrder(n->right); //recurse on the right
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// Card value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
CardBST::Node* CardBST::getNodeFor(Card value, Node* n) const{
    // base case
    //1st base case, we didn't find
    if (!n) {
        return NULL; //if there isn't anything there, we didn't find the value
    }
    //second base case, we got it
    if (n->info == value) {
        return n;
    }
    // recursive cases
    if (value < n->info) {
        return getNodeFor(value, n->left); //recurse on the left as we are smaller
    } else {
        return getNodeFor(value, n->right); //recurse on the right as we are larger
    }
}

// returns true if value is in the tree; false if not
bool CardBST::contains(Card value) const {
    return getNodeFor(value, root) != NULL; //if we get a node back, then it is in the tree, otherwise it is not.
    // != Null is saying doesn't not exist or it that it DOES exist, so in that case we return true, and false otherwise (Null != NUll is false)
}


// returns the Node containing the predecessor of the given value
CardBST::Node* CardBST::getPredecessorNode(Card value) const{
    Node* n = getNodeFor(value, root); //get the node for the value
    if (!n) {
        return NULL; //if there is no node for the value, then there is no predecessor
    }

    // case 1: left subtree exists, predecessor is the rightmost node of the left subtree
    if (n->left) {
        n = n->left; //start at the left subtree
        while (n->right) { //stop one step early so n is still valid
            n = n->right;
        }
        return n; //rightmost node of left subtree = predecessor
    }

    // case 2: no left subtree, go up until we find a predecessor in their left tree
    Node* parent = n->parent;
    while (parent && n == parent->left) { //if we are always a left child, there is no predecessor
        n = parent;
        parent = parent->parent;
    }
    return parent; // returns null if we are the leftmost node, otherwise the parent WHICH IS PREDECCESOR if n is a right child, as this is after loop breaks
}

// returns the successor value of the given value or 0 if there is none
CardBST::Node* CardBST::getSuccessorNode(Card value) const{
    //basically same as get predecessor node but with right and left switched, since successor is the next LARGEST val

    Node* n = getNodeFor(value, root);
    if (!n) {
        return NULL; 
    }

    // right subtree is case 1 where the successor is the leftmost value in it
    if (n->right) {
        n = n->right; 
        while (n->left) { 
            n = n->left;
        }
        return n; 
    }

    // case 2 going up until our value is a left child of one of the parents
    Node* parent = n->parent;
    while (parent && n == parent->right) { 
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardBST::remove(Card value) {
    // find the node to delete
    Node* target = getNodeFor(value, root);
    
    if (!target) {
        return false; // case 1, target doesn't exist
    }

    // if node has 2 children
    if (target->left != NULL && target->right != NULL) {
        Node* successor = getSuccessorNode(target->info);
        
        target->info = successor->info;
        
        // now we can delete the successor as it won't have a left child
        target = successor; 
    }

    // node has one or no children, we can delete it directly
    Node* child = NULL;

    if (target->left != NULL) {
        child = target->left;
    } else {
        child = target->right;
    }

    // update child's parent pointer if child exists
    if (child != NULL) {
        child->parent = target->parent;
    }

    //update where the parent points to 
    if (target->parent == NULL) {
        // if our target has no parent it is the root
        root = child;
    } else if (target == target->parent->left) { //if traget was a left child...
        target->parent->left = child;
    } else { //target is a right child
        target->parent->right = child;
    }

    //delete the isolated node now that it won't mess up any connections in the tree
    delete target;
    return true;
}


//iterator operators

CardBST::Iterator& CardBST::Iterator::operator++() {
    // just finds successor of current node, so the logic is the same as getsuccessornode

    // case 1: right subtree exists, go to leftmost node of right subtree
    if (current->right) {
        current = current->right;
        while (current->left) {
            current = current->left;
        }
    } else {
        // case 2: go up until we're a left child
        Node* p = current->parent;
        while (p && current == p->right) {
            current = p;
            p = p->parent;
        }
        current = p; // nullptr if we were the largest node
    }
    return *this;
}


//same as ++ but with predecessor

CardBST::Iterator& CardBST::Iterator::operator--() {
    // case 1: left subtree exists, go to rightmost node of left subtree
    if (current->left) {
        current = current->left;
        while (current->right) {
            current = current->right;
        }
    } else {
        // case 2: go up while we are a left child
        Node* p = current->parent;
        while (p && current == p->left) {
            current = p;
            p = p->parent;
        }
        current = p; // nullptr if we were the largest node
    }
    return *this;
}


Card CardBST::Iterator::operator*() const {
    return current->info; //dereference the info
}

bool CardBST::Iterator::operator==(const Iterator& other) const {
    return current == other.current; //iterators are equal if they point to the same thing
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
    return current != other.current; // not equal if they point to different nodes
}

//begin, end, rbegin, and rend for iteration

CardBST::Iterator CardBST::begin() const {
    if (!root) 
        return Iterator(nullptr); //empty tree w/ no beginning

    Node* n = root; 
    while (n->left) 
        n = n->left; // go as far left as possible to find smallest card

    return Iterator(n);
}

CardBST::Iterator CardBST::end() const {
    return Iterator(nullptr); //the end is always a nullptr
}

CardBST::Iterator CardBST::rbegin() const {
    if (!root) 
        return Iterator(nullptr); //empty w/ no beginning

    Node* n = root;
    while (n->right) 
        n = n->right; //go as far right as possible to find largest card
    return Iterator(n);
}

CardBST::Iterator CardBST::rend() const {
    return Iterator(nullptr); //rend is also always a nullptr, one past the smallest element
}

//same logic as playing the game in main_set.cpp but this time with BSTs instead of sets

void playGame(CardBST& alice, CardBST& bob) {
    bool matchfound = true;

    while (matchfound) {
        matchfound = false;

        // alice's turn is forward thru her cards
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                cout << "Alice picked matching card " << *it << endl;
                Card matched = *it;
                alice.remove(matched);
                bob.remove(matched);
                matchfound = true;
                break;
            }
        }

        if (matchfound) {
            // bobs turn is backwards through his, we only run bob's turn if alice found a match, otherwise no matches and we are done
            bool bobFound = false;
            for (auto it = bob.rbegin(); it != bob.rend(); --it) {
                if (alice.contains(*it)) {
                    cout << "Bob picked matching card " << *it << endl;
                    Card matched = *it;
                    bob.remove(matched);
                    alice.remove(matched);
                    matchfound = true;
                    bobFound = true;
                    break;
                }
            }
            if (!bobFound) matchfound = false;
        }
    }

    // print remaining hands
    cout << "\nAlice's cards:" << endl;
    for (auto it = alice.begin(); it != alice.end(); ++it) {
        cout << *it << endl;
    }

    cout << "\nBob's cards:" << endl;
    for (auto it = bob.begin(); it != bob.end(); ++it) {
        cout << *it << endl;
    }
}