//Nicholas Tai
#include "Letterbag.h"
#include <iostream>
using namespace std;

int LetterBag::getFrequency(char c) const // count occurrences of c
{
    if (!inRange(c))
        return 0;           // return false
    return counts[c - 'a'];
}

bool LetterBag::inRange(char c) // return true if c is a legal letter 'a' to 'z'
{
    return 'a' <= c && c <= 'z';
}

LetterBag::LetterBag() // no-parameter constructor for an empty LetterBag.
{
}

LetterBag::LetterBag(const vector<char> &v)  // initialize using letters in v, omitting non letters
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] >= 'a' && v[i] <= 'z')
        {
            ++counts[v[i] - 'a'];
            ++size;
        }
    }
}

bool LetterBag::operator==(const LetterBag & other) const  // return true iff *this equals other
{
    if (size != other.size)
        return false;
    for (int i = 0; i < 26; i++)
    {
        if (this->counts[i] != other.counts[i])
            return false;
    }
    return true;
}

bool LetterBag::operator!=(const LetterBag & other) const  // return false iff *this equals other
{
    return (!(*this == other));
}

int LetterBag::getCurrentSize() const  // return the current size of the LetterBag
{
    return size;
}

bool LetterBag::isEmpty() const  // return true iff the LetterBag is empty
{
    if (size)
        return false;
    return true;
}

LetterBag & LetterBag::add(char c) // add an occurrence of c to the LetterBag
{
    ++counts[c - 97];
    ++size;
    return *this;
}
LetterBag & LetterBag::remove(char c) // remove one occurrence of c (if there is one).
{
    --counts[c - 97];
    --size;
    return *this;
}
LetterBag & LetterBag::clear() // remove all occurrences of all letters
{
    size = 0;
    for (int i = 0; i < 26; i++)
        counts[i] = 0;
    return *this;
}

vector<char> LetterBag::toVector() const // return a vector with the letters in this object, in sorted order.
{
    vector<char> temp;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < counts[i]; j++)
                temp.push_back(i + 97);
    }
    return temp;
}

string LetterBag::toString() const // return a string with the letters in this object, in sorted order.
{
    string temp;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < counts[i]; j++)
            temp.push_back(i + 97);
    }
    return temp;
}
bool LetterBag::isSubbag(const LetterBag & other) const  // return true if *this is a subbag of other.
{
    if (*this == other)
        return true;
    if (this->getCurrentSize() > other.getCurrentSize())
        return false;
    // Must mean that this->size < other.size if passed both cases above
    for (int i = 0; i < 26; i++)
    {
        if (this->counts[i] > other.counts[i])
            return false;
    }
    return true;
}
