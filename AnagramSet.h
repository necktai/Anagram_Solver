//
//  AnagramSet.h
//  hash_program_V1
//
//  Created by Nick Tai on 11/12/17.
//  Copyright © 2017 Nick Tai. All rights reserved.
//

#ifndef AnagramSet_h
#define AnagramSet_h

#include <string>
#include <iostream>
#include "OList.h"
#include "Letterbag.h"

class AnagramSet
{
    friend ostream &operator<< (ostream & out, const AnagramSet &x);    // output anagram set

public:             // bad form
    LetterBag key;
    OList<string> words;
    bool isAnagramEmpty();
    int getSize();
    
};

#endif /* AnagramSet_h */
