#ifndef OUTPUT_H
#define OUTPUT_H

#include "resultline.h"
#include "filereader.h"

class Output
{
public:
    Output(char printTypeFlag, FileReader* fileReader, std::string& fileReaderMethod);
    void printResults();
    ~Output();

private:
    char printType;
    FileReader* fr;
    std::string frMethod; //tests
    //std::string* colorList;
    //static int colorIt;

    //std::string chooseColor();
};

#endif // OUTPUT_H
