// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  CardBST alice; //BST to store alice's cards instead of the set

  while (getline (cardFile1, line) && (line.length() > 0)){
    //extract the value first as a integer
    if (line[2] == 'a') { //line[2] holds the value from 'suit space value'
      alice.insert(Card(line[0], 1));
    } else if (line[2] == 'j') {
      alice.insert(Card(line[0], 11));
    } else if (line[2] == 'q') {
      alice.insert(Card(line[0], 12));
    } else if (line[2] == 'k') {
      alice.insert(Card(line[0], 13));
    } else {
      alice.insert(Card(line[0], stoi(line.substr(2)))); //if a double digit, substr captures the rest
    }
  }
  cardFile1.close();

  CardBST bob; //BST to store bob's cards

  while (getline (cardFile2, line) && (line.length() > 0)){
    //same as alice's while loop but changing the BST to bob

    //extract the value first as a integer
    if (line[2] == 'a') { //line[2] holds the value from 'suit space value'
      bob.insert(Card(line[0], 1));
    } else if (line[2] == 'j') {
      bob.insert(Card(line[0], 11));
    } else if (line[2] == 'q') {
      bob.insert(Card(line[0], 12));
    } else if (line[2] == 'k') {
      bob.insert(Card(line[0], 13));
    } else {
      bob.insert(Card(line[0], stoi(line.substr(2)))); //if a double digit, substr captures the rest
    }
  }
  cardFile2.close();
  
  //play the game using the playGame function defined in card_list.cpp, makes this way shorter than the set implementation
  playGame(alice, bob);

  return 0;
}