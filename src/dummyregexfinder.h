///
///      @file  dummyregexfinder.h
///     @brief  Regex finder that uses a simple strstr(...) function to compare line with expression
///
///
///    @author  Adam Syrek, adam.syrek@gmail.com
///
/// This source code is released for free distribution under the terms of the
/// GNU General Public License as published by the Free Software Foundation.
///=====================================================================================
///



#ifndef DUMMYREGEXFINDER_H
#define DUMMYREGEXFINDER_H

#include "regexfinder.h"
#include "resultline.h"


///
/// @class DummyRegexFinder
/// @brief Regex finder that implements strstr(...) function to compare line with expression. For informations about methods see RegexFinder class
///
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
