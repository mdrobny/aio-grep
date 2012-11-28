#include "dummyregexfinder.h"
#include <iostream>
DummyRegexFinder::DummyRegexFinder() : RegexFinder()
{
}

bool DummyRegexFinder::checkLine(ResultLine &line)
{
    std::string str = line.getLine();
    size_t pos = 0;
    bool found = false;
    while( (pos = str.find(regex, pos)) != std::string::npos) {
        int_pair_t occurence = std::make_pair(pos, pos + regex.length());
        line.addOccurence(occurence);
        pos = pos + regex.length();
        found = true;
    }

    return found;
}
