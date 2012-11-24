#ifndef ASYNCHRONOUSFILEREADER_H
#define ASYNCHRONOUSFILEREADER_H

#include <iostream>
#include "filereader.h"

class AsynchronousFileReader : public FileReader
{
public:
    AsynchronousFileReader(int argc, char** argv, RegexFinder *&rf);
};

#endif // ASYNCHRONOUSFILEREADER_H
