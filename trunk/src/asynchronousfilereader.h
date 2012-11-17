#ifndef ASYNCHRONOUSFILEREADER_H
#define ASYNCHRONOUSFILEREADER_H

#include <iostream>
#include "filereader.h"

class AsynchronousFileReader : public FileReader
{
public:
    AsynchronousFileReader(int argc, char** argv);
};

#endif // ASYNCHRONOUSFILEREADER_H
