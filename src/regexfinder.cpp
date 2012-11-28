#include "regexfinder.h"

RegexFinder::RegexFinder()
{
}

RegexFinder::RegexFinder(std::string r) :
    regex(r)
{
}

void RegexFinder::setRegex(std::string r)
{
    regex = r;
}

RegexFinder::~RegexFinder()
{
}
