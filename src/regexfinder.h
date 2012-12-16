#ifndef REGEXFINDER_H
#define REGEXFINDER_H

#include "resultline.h"
#include <string>

class RegexFinder
{
public:
    RegexFinder();
    virtual bool checkLine(ResultLine& line) = 0;
    virtual bool checkLineChar(ResultLine& line) = 0;
    virtual void setRegex(std::string r) = 0;
    virtual ~RegexFinder();
};

#endif // REGEXFINDER_H
