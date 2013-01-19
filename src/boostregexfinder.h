#ifndef CPP11REGEXFINDER_H
#define CPP11REGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"
#include <boost/regex.hpp>

class BoostRegexFinder
    : public RegexFinder
{
private:
    boost::regex regex;
public:
    BoostRegexFinder();
    BoostRegexFinder(std::string r);
    virtual bool checkLine(ResultLine& line);
    virtual bool checkLineChar(ResultLine& line);
    virtual void setRegex(std::string r);
    virtual ~BoostRegexFinder();
};

#endif //CPP11REGEXFINDER_H
