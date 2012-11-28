#ifndef REGEXFINDER_H
#define REGEXFINDER_H

#include "resultline.h"
#include <string>

class RegexFinder
{
protected:
    std::string regex;
public:
    RegexFinder();
    RegexFinder(std::string r);
    virtual bool checkLine(ResultLine& line) = 0;
    virtual void setRegex(std::string r);
    virtual ~RegexFinder();
};

#endif // REGEXFINDER_H
