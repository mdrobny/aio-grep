#include "boostregexfinder.h"

BoostRegexFinder::BoostRegexFinder()
    : RegexFinder()
{
}

BoostRegexFinder::BoostRegexFinder(std::string r)
{
    regex = boost::regex(r.c_str(), boost::regex_constants::grep);
}

bool BoostRegexFinder::checkLine(ResultLine& line)
{
    std::string str = line.getLine();
    bool found = false;
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    boost::sregex_iterator rgx_start(start, end, regex);
    boost::sregex_iterator rgx_end;
    for(; rgx_start != rgx_end; ++rgx_start)
    {
        found = true;
        int first = std::distance(start, (*rgx_start)[0].first);
        int second = std::distance(start, (*rgx_start)[0].second);
        line.addOccurence(int_pair_t(first, second));
    }
    return found;

}
void BoostRegexFinder::setRegex(std::string r)
{
    regex = boost::regex(r);
}

BoostRegexFinder::~BoostRegexFinder() {}

