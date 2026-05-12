#include <iostream>
#include "card_list.h"
using namespace std;

// used ai to write the test cases, I know what each of them is supposed to do but this would've been so much effort otherwise

int main() {
    // Test 1: insert into empty tree
    CardBST tree1;
    cout << "Insert into empty tree: " << tree1.insert(Card('c', 1)) << " (expected 1)" << endl;

    // Test 2: insert multiple cards
    cout << "Insert second card: " << tree1.insert(Card('h', 5)) << " (expected 1)" << endl;

    // Test 3: insert duplicate
    cout << "Insert duplicate: " << tree1.insert(Card('c', 1)) << " (expected 0)" << endl;

    // Test 4: insert same suit different value
    cout << "Insert same suit diff value: " << tree1.insert(Card('c', 13)) << " (expected 1)" << endl;

    // Test 5: insert different suit same value
    cout << "Insert diff suit same value: " << tree1.insert(Card('d', 1)) << " (expected 1)" << endl;

    // Test 6: contains on empty tree
    CardBST tree2;
    cout << "Contains on empty tree: " << tree2.contains(Card('c', 1)) << " (expected 0)" << endl;

    // Test 7: contains existing card
    tree2.insert(Card('h', 13));
    cout << "Contains existing card: " << tree2.contains(Card('h', 13)) << " (expected 1)" << endl;

    // Test 8: contains non-existing card
    cout << "Contains non-existing: " << tree2.contains(Card('h', 12)) << " (expected 0)" << endl;

    // Test 9: contains wrong suit
    cout << "Contains wrong suit: " << tree2.contains(Card('s', 13)) << " (expected 0)" << endl;

    // Test 10: contains after removal
    tree2.remove(Card('h', 13));
    cout << "Contains after removal: " << tree2.contains(Card('h', 13)) << " (expected 0)" << endl;

    // Test 11: remove from empty tree
    CardBST tree3;
    cout << "Remove from empty tree: " << tree3.remove(Card('c', 1)) << " (expected 0)" << endl;

    // Test 12: remove existing card
    tree3.insert(Card('c', 1));
    cout << "Remove existing card: " << tree3.remove(Card('c', 1)) << " (expected 1)" << endl;

    // Test 13: remove non-existing card
    tree3.insert(Card('h', 5));
    cout << "Remove non-existing: " << tree3.remove(Card('h', 6)) << " (expected 0)" << endl;

    // Test 14: remove node with two children
    CardBST tree4;
    tree4.insert(Card('d', 5));
    tree4.insert(Card('c', 3));
    tree4.insert(Card('h', 7));
    cout << "Remove node with two children: " << tree4.remove(Card('d', 5)) << " (expected 1)" << endl;
    cout << "Children still exist: " << tree4.contains(Card('c', 3)) << " " << tree4.contains(Card('h', 7)) << " (expected 1 1)" << endl;

    // Test 15: remove last card
    CardBST tree5;
    tree5.insert(Card('c', 1));
    tree5.remove(Card('c', 1));
    cout << "Tree empty after removing last: " << tree5.contains(Card('c', 1)) << " (expected 0)" << endl;

    // Test 16: print empty tree
    CardBST tree6;
    cout << "Print empty tree (should be nothing):" << endl;
    tree6.printInOrder();

    // Test 17: print single card
    tree6.insert(Card('c', 1));
    cout << "Print single card (expected c a):" << endl;
    tree6.printInOrder();

    // Test 18: print multiple cards in order
    CardBST tree7;
    tree7.insert(Card('h', 9));
    tree7.insert(Card('c', 1));
    tree7.insert(Card('d', 3));
    cout << "Print three cards (expected c a, d 3, h 9):" << endl;
    tree7.printInOrder();

    // Test 19: print after removal
    tree7.remove(Card('d', 3));
    cout << "Print after removal (expected c a, h 9):" << endl;
    tree7.printInOrder();

    // Test 20: print same suit different values
    CardBST tree8;
    tree8.insert(Card('c', 13));
    tree8.insert(Card('c', 1));
    tree8.insert(Card('c', 5));
    cout << "Print same suit (expected c a, c 5, c k):" << endl;
    tree8.printInOrder();

    // Test 21: begin == end on empty tree
    CardBST tree9;
    cout << "Empty tree begin==end: " << (tree9.begin() == tree9.end()) << " (expected 1)" << endl;

    // Test 22: single node forward
    tree9.insert(Card('c', 5));
    auto it = tree9.begin();
    cout << "Single node begin: " << *it << " (expected c 5)" << endl;

    // Test 23: forward iteration order
    CardBST tree10;
    tree10.insert(Card('h', 9));
    tree10.insert(Card('c', 1));
    tree10.insert(Card('d', 3));
    cout << "Forward iteration (expected c a, d 3, h 9):" << endl;
    for (auto it = tree10.begin(); it != tree10.end(); ++it) {
        cout << *it << endl;
    }

    // Test 24: reverse iteration order
    cout << "Reverse iteration (expected h 9, d 3, c a):" << endl;
    for (auto it = tree10.rbegin(); it != tree10.rend(); --it) {
        cout << *it << endl;
    }

    // Test 25: iterator != works
    CardBST tree11;
    tree11.insert(Card('c', 1));
    tree11.insert(Card('h', 1));
    cout << "begin != rbegin: " << (tree11.begin() != tree11.rbegin()) << " (expected 1)" << endl;

    // Test 26: game with common cards
    CardBST alice1, bob1;
    alice1.insert(Card('c', 3));
    alice1.insert(Card('h', 10));
    bob1.insert(Card('c', 3));
    bob1.insert(Card('h', 10));
    cout << "Test 26 - game with common cards:" << endl;
    playGame(alice1, bob1);

    // Test 27: game with one empty hand
    CardBST alice2, bob2;
    alice2.insert(Card('c', 1));
    cout << "Test 27 - game with one empty hand:" << endl;
    playGame(alice2, bob2);

    // Test 28: game with no common cards
    CardBST alice3, bob3;
    alice3.insert(Card('c', 1));
    bob3.insert(Card('h', 3));
    cout << "Test 28 - game with no common cards:" << endl;
    playGame(alice3, bob3);

    cout << "\nAll tests complete!" << endl;
    return 0;
}