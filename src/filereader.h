#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string>
#include <vector>
#include "ResultLine.h"

class FileReader
{

private:
    std::vector<std::string > fileList;
public:
    virtual FileReader(char** argv);
    virtual ResultLine readLine() = 0;
    virtual ~FileReader();

};

#endif // FILEREADER_H
