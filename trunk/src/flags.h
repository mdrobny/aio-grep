#ifndef FLAGS_H
#define FLAGS_H

#include "synchronousfilereader.h"
#include "asynchronousfilereader.h"
#include "mmapfilereader.h"
#include "regexfinder.h"

#include "dummyregexfinder.h"
#include "boostregexfinder.h"

#include <unistd.h>     //getoption function

///
/// @brief Parses flags and creates proper RegexFinder and FileReader
/// @author Michał Drobniak
///
class Flags
{
public:
    ///
    /// @brief Constructor parses passed flags and sets proper atributes in class
    /// calls initRegexFinder
    /// creates FileReader
    ///
    Flags(int argc, char** argv);
    FileReader* getFileReader();
    ~Flags();

    char methodChar; //passed to Output object
    char* flagsChar; //output flags passed to Output object
    bool getPrintSummaryFlag();
    bool getColorLines();

private:
    ///
    /// @brief corrects argument list by removing all parsed flag from argv
    ///
    void correctArgs(int& argc, char** argv,int optind);
    ///
    /// @brief initialize RegexFinder
    /// @param rgx - regex string, type - type of RegexFinder
    ///
    RegexFinder* initRegexFinder(char *rgx, char type);
    RegexFinder* rf;
    FileReader* fr;
    bool printSummary;
    bool colorLines;
    void printHelpAndExit();

};

#endif // FLAGS_H
