#ifndef FLAGS_H
#define FLAGS_H

#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "regexfinder.h"

#include "dummyregexfinder.h"
#include "boostregexfinder.h"
#include "re2regexfinder.h"

#include <unistd.h>     //getoption function

class Flags
{
public:
    Flags(int argc, char** argv);
    FileReader* getFileReader();
    ~Flags();

    char methodChar; //passed to Output object
    char* flagsChar; //output flags passed to Output object

private:
    void correctArgs(int& argc, char** argv,int optind);
    RegexFinder* initRegexFinder(std::string rgx);
    RegexFinder* rf;
    FileReader* fr;

};

#endif // FLAGS_H