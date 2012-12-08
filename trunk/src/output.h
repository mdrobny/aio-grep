#ifndef OUTPUT_H
#define OUTPUT_H

#include "resultline.h"
#include "timer.h"

class Output
{
public:
    Output(char printTypeFlag, std::string& fileReaderMethod);
    void printResult(ResultLine& l);
    void printSummary(Timer& time);
    ~Output();

private:
    char printType;
    std::string frMethod; //tests
    int totalOcc;     //total occurences amount
    //std::string* colorList;
    //static int colorIt;

    //std::string chooseColor();
};

#endif // OUTPUT_H
