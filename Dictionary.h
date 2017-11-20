//
//  Dictionary.h
//  hash_program_V1
//
//  Created by Nick Tai on 11/12/17.
//  Copyright © 2017 Nick Tai. All rights reserved.
//

#ifndef Dictionary_h
#define Dictionary_h

#include "AnagramSet.h"
#include <string>
using namespace std;

class Dictionary
{
private:
    struct item
    {
        AnagramSet set;
        item *next;
    };
    item **HashTable;
    int sizeOfTable;
public:
    int numCollisions = 0;
    int numWords = 0;
    int hash_key(string key);
    Dictionary(int tableSize);
    Dictionary(string wordList[], int numWords, int tableSize);
    void insert(string word);
    void remove(string word);
    bool contains(string word); // for counting exact words
    bool findSet(string word);
    AnagramSet getSet(string word);
    friend ostream &operator<< (ostream & out,const Dictionary &x);    // output anagram set
    
};
#endif /* Dictionary_h */

/*
ERROR

1. letter bag == was incorrect, had to change a variable in for loop
2. dictionary << operator was incorrect as it did not cout entire index list
3. Olist assignment operator was incorrect, did not account for cases with one letter
4. << operator for anagramSet must have the right parameter to be const
5. my contains at first only checked for the key but its suppose to check through the entire index list
6. i wrote (HashTable[index]->set.key == key) inside of the else case instead of temp->set.words.find(word)
7. similar to #5, I didn't check the entire index list for the one word I wanted to remove
8. Also, I deleted an item if the key matched but that only happens if It only has one word left to remove it
    else It just removes the word in the list
9. In order to use more efficient hash algorithims while also keeping anagrams to the same index is to sort the words in alphabetical order and then hash
10. actually, my hash function was incorrect which caused my contain to be incorrect. I don't actually need to use .find for contains, this is b/c anagrams are already hashed to the same index. So as long as the word is in the same index location with the same key, that shows that the palindrome exist AND you can solve anagrams from jumbled words with the contain function
11. jk #10 was wrong.
12. I made a seperate function for the issue i was facing. However, I had to change on line in the driver for this to work. Specifically in the unscramble I used findSet instead of contains.
*/
