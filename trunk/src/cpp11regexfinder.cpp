#include "cpp11regexfinder.h"
#include <regex>

Cpp11RegexFinder::Cpp11RegexFinder()
    : RegexFinder()
{
}

Cpp11RegexFinder::Cpp11RegexFinder(std::string r)
{
    regex = std::regex(r.c_str());
}

bool Cpp11RegexFinder::checkLine(ResultLine& line)
{
    std::smatch match;
    std::string str = line.getLine();
    std::regex_match(str.cbegin(), str.cend(), match, regex);
    int i=match.size();
    bool found = false;
    while( i != 0 )
    {
        line.addOccurence(int_pair_t(match.position(i-1), match.position(i-1) + match.length(i-1)));
        found = true;
        --i;
    }
    return found;
}
void Cpp11RegexFinder::setRegex(std::string r)
{
    regex = std::regex(r.c_str());
    regex = std::regex("(main)");
}

Cpp11RegexFinder::~Cpp11RegexFinder() {};
