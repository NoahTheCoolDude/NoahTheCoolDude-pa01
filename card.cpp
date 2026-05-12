// card.cpp
// Author: Noah Ruderman
// Implementation of the classes defined in card.h

#include "card.h"
using namespace std;

//use Card:: as the scope for all because we are outside of the class now

Card::Card(char s, int v) {
    suit = s;
    value = v; //makes a card with suit of the char passed in and the value passed in
}

int Card::suittoint() const { //convert the suit to an int for comparison later
    if (suit == 'c') {
        return 0;
    } else if (suit == 'd') {
        return 1;
    } else if (suit == 's') {
        return 2;
    } else if (suit == 'h') {
        return 3;
    } else { //invalid suit, so do -1
        return -1; 
    }
 
}


bool Card::operator<(const Card& right) const {
    //suit is precedent and then value
    if (suittoint() < right.suittoint()) { //check if our left (this) card is less than right on suit
        return true;
    } else if (suittoint() == right.suittoint()) {
        if (value < right.value) {
            return true;
        } else {
            return false;
        }
    }

    return false; //suit is greater so false
}

bool Card::operator==(const Card& right) const {
    if (suit == right.suit && value == right.value) {
        return true; //only equal when they have same suit and value, can compare chars directly
    }
    return false;
}

bool Card::operator>(const Card& right) const { // same as less than but flipped
    //suit is precedent and then value
    if (suittoint() > right.suittoint()) { //check if our left (this) card is less than right on suit
        return true;
    } else if (suittoint() == right.suittoint()) {
        if (value > right.value) {
            return true;
        } else {
            return false;
        }
    }

    return false; //suit is greater so false
}

ostream& operator<<(ostream& os, const Card& card) { //can remove the stds as now using namespace std, no scope operator as defined outside of class
    os << card.suit << " ";

    if (card.value == 1) {
        os << 'a';
    } else if (card.value == 11) {
        os << 'j';
    } else if (card.value == 12) {
        os << 'q';
    } else if (card.value == 13) {
        os << 'k';
    } else {
        os << card.value;
    }

    return os;
}