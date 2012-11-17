#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include "ResultLine.h"

class FileReader
{

protected:
    std::vector<std::string > fileList;
public:
    FileReader(int argc, char** argv);
    virtual ResultLine readLine() = 0;
    virtual ~FileReader();

};

#endif // FILEREADER_H
