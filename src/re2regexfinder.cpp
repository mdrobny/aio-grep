#include "re2regexfinder.h"

RE2RegexFinder::RE2RegexFinder(std::string& r)
    : RegexFinder(), pattern(r.c_str()), regex(r)
{

}

bool RE2RegexFinder::checkLine(ResultLine &line)
{
    std::string str = line.getLine();
    re2::StringPiece input(str);
    std::string var;
    bool found = false;
    while(re2::RE2::FindAndConsume(&input, pattern, &var))
    {
        found = true;
        int first = str.length() - input.length() - var.length();
        int last = str.length() - input.length();
        line.addOccurence(int_pair_t(first, last));
    }
    return found;
}


RE2RegexFinder::~RE2RegexFinder()
{
}


void RE2RegexFinder::setRegex(std::string r)
{
    regex = r;
}
