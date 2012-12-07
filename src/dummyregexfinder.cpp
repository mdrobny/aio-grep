#include "dummyregexfinder.h"
#include <iostream>

DummyRegexFinder::DummyRegexFinder(std::string str) : RegexFinder()
{
    rgx = str;
}

bool DummyRegexFinder::checkLine(ResultLine &line)
{
    std::string str = line.getLine();
    size_t pos = 0;
    bool found = false;
    while( (pos = str.find(rgx, pos)) != std::string::npos) {
        int_pair_t occurence = std::make_pair(pos, pos + rgx.length());
        line.addOccurence(occurence);
        pos = pos + rgx.length();
        found = true;
    }

    return found;
    //4 debug if u want to print every line to check if they are read correctly
    //std::cout << str <<std::endl;
    return false;
}

void DummyRegexFinder::setRegex(std::string str)
{
    rgx = str;
}
