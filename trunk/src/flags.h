#ifndef FLAGS_H
#define FLAGS_H

#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "mmapfilereader.h"
#include "regexfinder.h"

#include "dummyregexfinder.h"
#include "boostregexfinder.h"

#include <unistd.h>     //getoption function

class Flags
{
public:
    Flags(int argc, char** argv);
    FileReader* getFileReader();
    ~Flags();

    char methodChar; //passed to Output object
    char* flagsChar; //output flags passed to Output object
    bool getPrintSummaryFlag();
    bool getColorLines();

private:
    void correctArgs(int& argc, char** argv,int optind);
    RegexFinder* initRegexFinder(char *rgx, char type);
    RegexFinder* rf;
    FileReader* fr;
    bool printSummary;
    bool colorLines;

};

#endif // FLAGS_H
