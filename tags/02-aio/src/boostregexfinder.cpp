#include "boostregexfinder.h"

BoostRegexFinder::BoostRegexFinder()
    : RegexFinder()
{
}

BoostRegexFinder::BoostRegexFinder(std::string r)
{
    regex = boost::regex(r);
}

bool BoostRegexFinder::checkLine(ResultLine& line)
{
    boost::smatch match; //info about matches
    std::string str = line.getLine();
    bool found = false;
    if( boost::regex_search(str, match, regex) == false)
    {
        return found;
    }
    for(int i=match.size(); i != 0; --i)
    {
        line.addOccurence(int_pair_t(match.position(i-1)+1, match.position(i-1) + match.length(i-1)+1));
        found = true;
    }
    return found;
}
void BoostRegexFinder::setRegex(std::string r)
{
    regex = boost::regex(r);
}

BoostRegexFinder::~BoostRegexFinder() {}
