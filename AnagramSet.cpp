// Nick Tai

#include "AnagramSet.h"
ostream &operator<< (ostream & out, const AnagramSet &x)
{
    x.words.print();
    return out;
}

bool AnagramSet::isAnagramEmpty()
{
    return words.isEmpty();
}

int AnagramSet::getSize()
{
    return words.getSize();
}
