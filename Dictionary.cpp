//
//  Dictionary.cpp
//  hash_program_V1
//
//  Created by Nick Tai on 11/12/17.
//  Copyright © 2017 Nick Tai. All rights reserved.
//

#include "Dictionary.h"
#include <cmath>
#include <cstring>

int Dictionary::hash_key(string key)
{
    LetterBag x;								// CRUCIAL. THIS IS SO THAT ANAGRAMS GET HASHED TO THE SAME INDEX.
    for (int i = 0; i < key.length(); i++)
        x.add(key[i]);
    key = x.toString();
    
    unsigned long int hash = 5381;
    for (int i = 0; i < key.length(); i++)
        hash = hash + key[key.length()-1-i] * pow(11, i);
    return hash % sizeOfTable;
}

Dictionary::Dictionary(int tableSize)
{
    HashTable = new item*[tableSize];
    sizeOfTable = tableSize;
    
    for (int i = 0; i < tableSize; i++)
        HashTable[i] = nullptr;
}

Dictionary::Dictionary(string wordList[], int numWords, int tableSize)
{
    HashTable = new item*[tableSize];
    sizeOfTable = tableSize;
    
    for (int i = 0; i < tableSize; i++)
        HashTable[i] = nullptr;
    for (int i = 0; i < numWords; i++)
        this->insert(wordList[i]);
}

void Dictionary::insert(string word)
{
    
    int index = hash_key(word);
    bool found = false;
    
    LetterBag key;
    for (int i = 0; i < word.length(); i++)             //to find matching anagram set
        key.add(word[i]);
    
    if (HashTable[index] == nullptr)                    // Case 1: Insert into empty bucket
    {
        HashTable[index] = new item;
        HashTable[index]->next = nullptr;
        
        if (!HashTable[index]->set.words.find(word))            // to handle duplicates
            HashTable[index]->set.words.insert(word);
        for (int i = 0; i < word.length(); i++)
            HashTable[index]->set.key.add(word[i]);
    }
    else if (HashTable[index]->set.key == key)          // Case 2: First bucket is the key
    {
        if (!HashTable[index]->set.words.find(word))
            HashTable[index]->set.words.insert(word);
    }
    else                                                // Case 3: Search index list for key
    {
        ++numCollisions;
        item *temp = HashTable[index];
        while (temp != nullptr && !found)
        {
            if (temp->set.key == key)
            {
                if (!temp->set.words.find(word))
                    temp->set.words.insert(word);
                found = true;
            }
            temp = temp->next;
        }
        if (!found)                                     // Case 3.1: Create new AnagramSet b/c key does not exist
        {
            item *current = HashTable[index];
            while (current->next != nullptr)
                current = current->next;
            
            item *new_item = new item;
            new_item->next = nullptr;
            for (int i = 0; i < word.length(); i++)
                new_item->set.key.add(word[i]);
            new_item->set.words.insert(word);
            
            current->next = new_item;
        }
    }
    ++numWords;
}

void Dictionary::remove(string word)
{
    int index = hash_key(word);
    item *del_ptr;
    item *p1;
    item *p2;

    LetterBag key;
    for (int i = 0; i < word.length(); i++)     //to find matching anagram set
        key.add(word[i]);
    
    if (HashTable[index] == nullptr)
    {
//        cout << word << " is not in table." << endl;
    }
    else if (HashTable[index]->set.key == key && HashTable[index]->next == nullptr) // Case 1: first bucket and only bucket
    {
        if(HashTable[index]->set.words.find(word))                      // look through list
        {
            if (HashTable[index]->set.words.getSize() == 1)             // only delete the entire node if it has one element left
            {
                del_ptr = HashTable[index];
                HashTable[index] = nullptr;
                delete del_ptr;
            }
            else
                HashTable[index]->set.words.remove(word);               // remove the word from list
        }
    }
    else if (HashTable[index]->set.key == key)						// b/c from the prev if statements, this means its Case 2: first bucket and first match
    {
        if(HashTable[index]->set.words.find(word))
        {
            if (HashTable[index]->set.words.getSize() == 1)
            {
                del_ptr = HashTable[index];
                HashTable[index] = HashTable[index]->next;
                delete del_ptr;
            }
            else
                HashTable[index]->set.words.remove(word);
        }
    }
    else														// Case 3: not in first bucket must go through nodes
    {
        p1 = HashTable[index]->next;
        p2 = HashTable[index];
        while (p1 != nullptr && p1->set.key != key)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if (p1 == nullptr)
        {
//            cout << "word was not found to be deleted." << endl;
        }
        else
        {
            if(p1->set.words.find(word))
            {
                if (p1->set.words.getSize() == 1)
                {
                    del_ptr = p1;
                    p1 = p1->next;
                    p2->next = p1;
                    delete del_ptr;
                }
                else
                    p1->set.words.remove(word);
            }
        }
    }
    --numWords;
}

bool Dictionary::contains(string word)
{
    for (int i = 0; i < word.length(); i++)			// for upper case inputs. Will be converted to lower case.
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] -= 'Z' - 'z';
    }
    
    int index = hash_key(word);

    LetterBag key;
    for (int i = 0; i < word.length(); i++) // to find matching anagram set
        key.add(word[i]);

    if (HashTable[index] == nullptr)
    {
        return false;
    }
    else if (HashTable[index]->set.key == key)
    {
        if(HashTable[index]->set.words.find(word))			// once in key aka correct set, go through it's list for the word
            return true;
    }
    else													// not in first node of bucket. must traverse
    {
        item *temp = HashTable[index];
        while (temp != nullptr)
        {
            if (temp->set.key == key)
            {
                if(temp->set.words.find(word))
                    return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

bool Dictionary::findSet(string word)				// same exact thing as contains except returns true when word's key value exists w
{													// this means that the set for that word exists
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] -= 'Z' - 'z';
    }
    
    int index = hash_key(word);
    
    LetterBag key;
    for (int i = 0; i < word.length(); i++) // to find matching anagram set
        key.add(word[i]);
    
    if (HashTable[index] == nullptr)
		return false;
    else if (HashTable[index]->set.key == key)
        return true;
    else
    {
        item *temp = HashTable[index];
        while (temp != nullptr)
        {
            if (temp->set.key == key)
            {
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

AnagramSet Dictionary::getSet(string word) // HOW DO I RETURN ANAGRAMSET IF IT DOES NOT EXIST
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] -= 'Z' - 'z';
    }
    
    int index = hash_key(word);
	
    LetterBag key;
    for (int i = 0; i < word.length(); i++) // to find matching anagram set
        key.add(word[i]);
    
    if (HashTable[index] == nullptr)
    {
        cout << word << " was not found in table." << endl;
        // throw exception??
    }
    else if (HashTable[index]->set.key == key)
    {
        return HashTable[index]->set;
    }
    else
    {
        item *temp = HashTable[index];
        while (temp != nullptr)
        {
            if (temp->set.key == key)
            {
                return temp->set;
            }
            temp = temp->next;
        }
            cout << "Word was not found." << endl;
    }
    
    return HashTable[index]->set;
    // return empty anagram set or maybe throw exception
}


ostream &operator<< (ostream & out,const Dictionary &x)    // output anagram set
{
    string temp;
    for (int i = 0; i < x.sizeOfTable; i++)
    {
        if (x.HashTable[i] != nullptr)					// basically a linked list output
        {
            Dictionary::item *current = x.HashTable[i];
            while (current != NULL)
            {
                cout << "{ ";
                temp = current->set.key.toString();
                cout << temp << ": ";
                cout << current->set << " }" << endl;
                current = current->next;
            }
        }
    }
    return out;
}
