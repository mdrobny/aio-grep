#include "filereader.h"

FileReader::FileReader(int argc, char **argv)
{

    regex = argv[1];

    for(int i = 2; i < argc; ++i)
    {
        std::string tmp(argv[i]);
        fileList.push_back(tmp);
    }
}

FileReader::~FileReader()
{
}