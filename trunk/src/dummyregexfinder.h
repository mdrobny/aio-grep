#ifndef DUMMYREGEXFINDER_H
#define DUMMYREGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"

class DummyRegexFinder : public RegexFinder
{
    private:
        const char* rgx;
public:

    DummyRegexFinder(char *str);
    virtual bool checkLine(ResultLine &line);
    virtual bool checkLineChar(ResultLine &line);
    virtual void setRegex(std::string str);

};

#endif // DUMMYREGEXFINDER_H
