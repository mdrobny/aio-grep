#ifndef SYNCHRONOUSFILEREADER_H
#define SYNCHRONOUSFILEREADER_H

#include <iostream>
#include <fstream>

#include "filereader.h"
#include "resultline.h"
#include <string.h>

class SynchronousFileReader : public FileReader
{
private:
    std::ifstream currentFile;
    int currentLine;
    std::string currentFilename;
    std::vector<std::string > fileList;
public:
    SynchronousFileReader(int argc, char** argv, RegexFinder*& rf);
    ReadResult readLine(ResultLine& line);
};

#endif // SYNCHRONOUSFILEREADER_H