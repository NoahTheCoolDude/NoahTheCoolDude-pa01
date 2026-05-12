// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

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
  set<Card> alice; //set to store alice's cards

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

  set<Card> bob; //bobs set of cards

  while (getline (cardFile2, line) && (line.length() > 0)){
    //same as alice's while loop but changing the set to bob

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
  
  //game logic, starting with alice's turn
//all of game logic must be in a while loop that only stops if we find a match

bool matchfound = true;

while (matchfound) {
  matchfound = false;
  //loop forward thru her set and check if bob has a card
  for (auto it = alice.begin(); it != alice.end(); ++it ) {
    if (bob.count(*it)) {
      cout << "Alice picked matching card " << *it << endl; //if it exists, print it
      Card matched = *it;
      bob.erase(matched); //erase from both sets with matched as still using iterator
      alice.erase(matched);

      matchfound = true; //ending the while loop, we got a match!

      break; //end the loop in that case
    }  

  }

  // bob's turn has same logic as alice's but going backwards with rbegin() and rend()
  // used claude to find out how to interate through the sets


  if (matchfound) { //only run bob's turn if alice found a match, otherwise we are done
    for (auto it = bob.rbegin(); it != bob.rend(); ++it ) {
      if (alice.count(*it)) {
        cout << "Bob picked matching card " << *it << endl; //if it exists, print it
        Card matched = *it;
        alice.erase(matched); //erase from both sets with matched as still using iterator
        bob.erase(matched);

        matchfound = true; //ending the while loop, we got a match!
        break; //end the loop in that case
      }  

    }
  }
}


//game finished, print the remaining hands

cout << "Alice's cards:" << endl;
for (auto it = alice.begin(); it != alice.end(); ++it) {
  cout << *it << endl; //print the card itself by dereferncing the pointer to it
}
  
cout << "\nBob's cards:" << endl;
for (auto it = bob.begin(); it != bob.end(); ++it) {
  cout << *it << endl; //print the card
}
  

  return 0;
}
