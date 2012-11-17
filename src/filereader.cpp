#include "filereader.h"

FileReader::FileReader(int argc, char **argv)
{
    for(int i = 1; i < argc; ++i)
    {
        // TODO: Add check for directories
        std::string tmp(argv[i]);
        fileList.push_back(tmp);
    }
}

FileReader::~FileReader()
{
}
