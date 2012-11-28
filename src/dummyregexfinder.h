#ifndef DUMMYREGEXFINDER_H
#define DUMMYREGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"

class DummyRegexFinder : public RegexFinder
{
    private:
        std::string rgx;
public:
    DummyRegexFinder();
    virtual bool checkLine(ResultLine &line);
    virtual void setRegex(std::string str);

};

#endif // DUMMYREGEXFINDER_H
