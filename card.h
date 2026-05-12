// card.h
// Author: Noah Ruderman
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
public:
    char suit;
    int value; //1 is ace, 2 is 2... 11 is jack, 12 is queen, 13 is king
    
    //constructor
    Card(char s, int v);

    //operators
    bool operator<(const Card& right) const; //compares what is on the left of < (this) to the Card on the right, ensuring nothing changes with const
    bool operator==(const Card& right) const;
    bool operator>(const Card& right) const;
    
    int suittoint() const; //to compare the suits later
}; 

//printing operator << on the outside of the class as it isn't a member function
// an outputstream type takes in the type of output stream to the left of << (usually cout) and a card that we don't modify on the right
std::ostream& operator<<(std::ostream& os, const Card& card); 

#endif
