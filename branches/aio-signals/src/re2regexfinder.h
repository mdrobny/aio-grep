#ifndef RE2REGEXFINDER_H
#define RE2REGEXFINDER_H

#include <re2/re2.h>
#include "regexfinder.h"
#include "resultline.h"
#include <string>

class RE2RegexFinder : public RegexFinder
{
private:
    std::string regex;
    re2::RE2 pattern;
public:
    RE2RegexFinder(std::string &r);
    virtual bool checkLine(ResultLine& line);
    virtual void setRegex(std::string r);
    virtual ~RE2RegexFinder();
};

#endif // RE2REGEXFINDER_H
