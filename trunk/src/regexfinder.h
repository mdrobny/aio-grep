#ifndef REGEXFINDER_H
#define REGEXFINDER_H

#include "resultline.h"
#include <string>
#include <regex>

class RegexFinder
{
protected:
    std::regex regex;
public:
    RegexFinder();
    RegexFinder(std::string r);
    virtual bool checkLine(ResultLine& line) = 0;
    virtual void setRegex(std::string r);
    virtual ~RegexFinder();
};

#endif // REGEXFINDER_H
