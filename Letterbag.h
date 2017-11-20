// Nicholas Tai

#ifndef LETTERBAG_H
#define LETTERBAG_H

#include <vector>
#include <iostream>
using namespace std;

class LetterBag
{
private:
	int counts[26] = {};         // no need to make 26 a named constant since the English alphabet never changes size
    static bool inRange(char c); // return true if c is a legal letter 'a' to 'z'
    int size = 0;

public:
    LetterBag() ;  // no-parameter constructor for an empty LetterBag.

    LetterBag(const vector<char> & v);  // initialize using letters in v, omitting non letters

    bool operator==(const LetterBag & other) const;  // return true iff *this equals other

    bool operator!=(const LetterBag & other) const;  // return false iff *this equals other

    int getCurrentSize() const;  // return the current size of the LetterBag

    bool isEmpty() const;  // return true iff the LetterBag is empty

    LetterBag & add(char c); // add an occurrence of c to the LetterBag

    LetterBag & remove(char c); // remove one occurrence of c (if there is one).

    LetterBag & clear(); // remove all occurrences of all letters

    int getFrequency(char c) const; // count occurrences of c

    vector<char> toVector() const; // return a vector with the letters in this object, in sorted order.

    bool isSubbag(const LetterBag & other) const;  // return true if *this is a subbag of other.
    
    string toString() const; // return a string with the letters in this object, in sorted order.

};

#endif

//  This tests a few operations but not everything. You need to do more.
