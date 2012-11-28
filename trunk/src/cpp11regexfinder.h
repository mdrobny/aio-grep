#ifndef CPP11REGEXFINDER_H
#define CPP11REGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"
#include <regex>

class Cpp11RegexFinder
    : public RegexFinder
{
public:
    Cpp11RegexFinder();
    Cpp11RegexFinder(std::string r);
    virtual bool checkLine(ResultLine& line);
    virtual void setRegex(std::string r);
    virtual ~Cpp11RegexFinder();
};

#endif //CPP11REGEXFINDER_H
