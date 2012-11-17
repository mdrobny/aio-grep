#ifndef SYNCHRONOUSFILEREADER_H
#define SYNCHRONOUSFILEREADER_H

#include <iostream>
#include <fstream>

#include "filereader.h"
#include "ResultLine.h"
#include <string.h>

class SynchronousFileReader : public FileReader
{
private:
    std::ifstream currentFile;
    int currentLine;
    std::string currentFilename;
public:
    SynchronousFileReader(int argc, char** argv);
    ReadResult readLine(ResultLine& line);
};

#endif // SYNCHRONOUSFILEREADER_H
