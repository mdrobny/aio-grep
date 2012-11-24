#ifndef DUMMYREGEXFINDER_H
#define DUMMYREGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"

class DummyRegexFinder : public RegexFinder
{
public:
    DummyRegexFinder();
    bool checkLine(ResultLine &line);

};

#endif // DUMMYREGEXFINDER_H
