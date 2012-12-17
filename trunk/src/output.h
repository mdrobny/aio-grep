#ifndef OUTPUT_H
#define OUTPUT_H

#include "resultline.h"
#include "timer.h"

class Output
{
public:
    Output(char methodChar,char* flagsChar);
    void printResult(ResultLine& l);
    void printSummary(Timer& time);

private:
    char flagLineNumbers;
    char flagFileNames;
    std::string currentFileName;
    std::string frMethod; //tests
    int totalOcc;     //total occurences amount
};

#endif // OUTPUT_H
