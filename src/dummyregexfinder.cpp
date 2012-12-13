#include "dummyregexfinder.h"
#include <iostream>
#include <cstring>

DummyRegexFinder::DummyRegexFinder(char *str) : RegexFinder()
{
    rgx = str;
}

bool DummyRegexFinder::checkLine(ResultLine &line)
{
    const char* str = line.getLine().c_str();
    const char* pos = 0;
    bool found = false;
    while( (pos = strstr(str, rgx)) != NULL) {
        int tmp = strlen(str) - strlen(pos);
        int_pair_t occurence = std::make_pair(tmp, tmp + strlen(rgx));
        line.addOccurence(occurence);
        str = pos + strlen(rgx);
        found = true;
    }

    return found;
    //4 debug if u want to print every line to check if they are read correctly
    //std::cout << str <<std::endl;
    //return false;
}

void DummyRegexFinder::setRegex(std::string str)
{
    rgx = str.c_str();
}
