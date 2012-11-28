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
    boost::smatch match;
    std::string str = line.getLine();
    bool found = false;
    if( boost::regex_match(str, match, regex) == false)
    {
        return found;
    }
    int i=match.size();
    while( i != 0 )
    {
        line.addOccurence(int_pair_t(match.position(i-1), match.position(i-1) + match.length(i-1)));
        found = true;
        --i;
    }
    return found;
}
void BoostRegexFinder::setRegex(std::string r)
{
    regex = boost::regex(r);
}

BoostRegexFinder::~BoostRegexFinder() {}
